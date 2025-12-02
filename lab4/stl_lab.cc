#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//
//   Har ni frågor om kompletteringen kan ni maila mig.

// Komplettering: Fånga exceptions på lämpligt sätt. Användaren ska aldrig behöva se “Terminate called after...”. 
// Komplettering: Felaktig hantering av undantag. Undantag bör endast kastas i exceptionella fall. 
// Kan vi kommunicera på något annat sätt vör vi göra det.

// Komplettering: Initiera alltid variabler med måsvingar.

struct Argument {
    std::string flag{};
    std::string parameter{};
};

struct WordFreq {
    std::string word{};
    int count{};
};

std::pair<std::string, std::string> parse_flag_by_delim(std::string const &string, char delim) {
    int delimiter_idx{static_cast<int>(string.find(delim))};
    return {string.substr(0, delimiter_idx), string.substr(delimiter_idx + 1)};
}

std::vector<std::string> extract_unique_words(std::vector<std::string> const &text) {
    std::vector<std::string> unique_words{};
    std::unique_copy(text.begin(), text.end(), std::back_inserter(unique_words));
    std::sort(unique_words.begin(), unique_words.end());
    unique_words.erase(std::unique(unique_words.begin(), unique_words.end()), unique_words.end());
    return unique_words;
}

std::vector<WordFreq> populate_word_freq(std::vector<std::string> const &text) {
    auto unique_words{extract_unique_words(text)};
    std::vector<WordFreq> freq_vector{unique_words.size()};

    // POPULATING THE VECTOR
    std::transform(unique_words.begin(),
                   unique_words.end(),
                   freq_vector.begin(),
                   [&text](std::string const &word) {
                       return WordFreq{
                           word, static_cast<int>(std::count(text.begin(), text.end(), word))};
                   });
    return freq_vector;
}

void output_word_freq(std::vector<WordFreq> const &freq_vector,
                      int longest_word,
                      bool align_right) {
    std::transform(freq_vector.begin(),
                   freq_vector.end(),
                   std::ostream_iterator<std::string>(std::cout, "\n"),
                   [longest_word, align_right](WordFreq const &wf) {
                       std::string buff(longest_word - wf.word.length(), ' ');
                       return (align_right ? "" : buff) + wf.word + (align_right ? buff : "") +
                              " " + std::to_string(wf.count);
                   });
    std::cout.flush();
}

// HANDLING THE FLAGS
void handle_print_flag(std::vector<std::string> const &text) {
    // OUTPUT
    std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "\n";
    std::cout.flush();
}

void handle_frequency_flag(std::vector<std::string> const &text, int longest_word) {
    auto freq_vector{populate_word_freq(text)};

    // SORTING
    std::sort(freq_vector.begin(), freq_vector.end(), [](WordFreq const &lhs, WordFreq const &rhs) {
        return lhs.count > rhs.count;
    });

    // OUTPUT
    output_word_freq(freq_vector, longest_word, true);
}

void handle_table_flag(std::vector<std::string> const &text, int longest_word) {
    auto freq_vector{populate_word_freq(text)};
    output_word_freq(freq_vector, longest_word, false);
}

void handle_substitute_flag(std::vector<std::string> &text, Argument const &arg) {
    auto parsed_subs = parse_flag_by_delim(arg.parameter, '+');

    std::string old_word = parsed_subs.first;
    std::string new_word = parsed_subs.second;

    if (new_word.empty() || old_word.empty()) {
    std::cout << "\n" << "Invalid input, atleast one empty paramater" << "\n" << std::endl;
    return;
    }

    if (arg.parameter.find('+') == std::string::npos) {
        std::cout << "\n" << "Wrong parameter type with no '+' for --subsitute" << "\n" << std::endl;
        return;
    }

    if(old_word + ('+') + new_word == old_word + ('+') + old_word) {
        std::cout << "\n" << "Tried to substitute old_word with the same word" << "\n" << std::endl;
        return;
    }

    std::replace(text.begin(), text.end(), old_word, new_word);
}

void handle_remove_flag(std::vector<std::string> &text, Argument const &arg) {
    text.erase(std::remove(text.begin(), text.end(), arg.parameter), text.end());
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        std::cout << "\n" << "Invalid input, correct format: ./a.out (path to text) flag(s)=(optional paramater)"
        << "\n" << std::endl;
        return 0;
    }

    try {
        std::ifstream file{(argv[1])};

        if (!file.is_open()) {
            throw std::runtime_error("Error opening the file!");
        }

    std::vector<std::string> text = {std::istream_iterator<std::string>(file),
                                     std::istream_iterator<std::string>()};

    // EXTRACTING ALL THE ARGS EXCEPT FOR THE FIRST 2
    std::vector<std::string> str_arguments(argv + 2, argv + argc);

    std::for_each(str_arguments.begin(),
                  str_arguments.end(),
                  [&text](std::string const &str_arg) {
                      int longest_word =
                          std::max_element(text.begin(),
                                           text.end(),
                                           [](std::string const &lhs, std::string const &rhs) {
                                               return lhs.length() < rhs.length();
                                           })
                              ->length();
                              
                      // PARSING THE FLAG
                      auto parsed_str_arg = parse_flag_by_delim(str_arg, '=');
                      Argument arg = {parsed_str_arg.first, parsed_str_arg.second};

                      // HANDLING THE FLAG
                      if (arg.flag == "--print") {
                          handle_print_flag(text);
                      } else if (arg.flag == "--frequency") {
                          handle_frequency_flag(text, longest_word);
                      } else if (arg.flag == "--table") {
                          handle_table_flag(text, longest_word);
                      } else if (arg.flag == "--substitute") {
                          handle_substitute_flag(text, arg);
                      } else if (arg.flag == "--remove") {
                          handle_remove_flag(text, arg);
                      } else {
                          std::cout << "Invalid flag: " << arg.flag << std::endl;
                      }
                  });
    } 
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } 
}