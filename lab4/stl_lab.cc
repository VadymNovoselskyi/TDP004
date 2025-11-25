#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct Argument {
    std::string flag;
    std::string parameter;
};

struct WordFreq {
    std::string word;
    int count;
};

std::pair<std::string, std::string> parse_flag_by_delim(std::string const &string, char delim) {
    int delimiter_idx{static_cast<int>(string.find(delim))};
    return {string.substr(0, delimiter_idx), string.substr(delimiter_idx + 1)};
}

void handle_print_flag(std::vector<std::string> const &text) {
    // OUTPUT
    std::for_each(text.begin(), text.end(), [](std::string word) { std::cout << word << " "; });
    std::cout.flush();
}

void handle_frequency_flag(std::vector<std::string> const &text, int const &longest_word) {
    std::vector<WordFreq> freq_vector{};

    // FILLING THE VECTOR
    std::for_each(text.begin(), text.end(), [&freq_vector](std::string word) {
        auto it = find_if(freq_vector.begin(), freq_vector.end(), [word](WordFreq wf) {
            return wf.word == word;
        });
        // IF THERE IS NO ENTRY FOR THAT WORD: PUSH NEW ONE
        if (it == freq_vector.end()) {
            freq_vector.push_back({word, 1});
        }
        // IF THERE IS A VALUE: INCREMENT ITS VALUE
        else {
            it->count++;
        }
    });

    // SORTING
    std::sort(freq_vector.begin(), freq_vector.end(), [](WordFreq lhs, WordFreq rhs) {
        return lhs.count > rhs.count;
    });

    // OUTPUT
    std::cout << std::right;
    std::for_each(freq_vector.begin(), freq_vector.end(), [longest_word](WordFreq wf) {
        std::cout << std::setw(longest_word) << wf.word << " " << wf.count << "\n";
    });
    std::cout.flush();
}

void handle_table_flag(std::vector<std::string> const &text, int const &longest_word) {
    std::map<std::string, int> freq_map{};

    // FILLING THE MAP
    std::for_each(text.begin(), text.end(), [&freq_map](std::string word) { freq_map[word]++; });

    // OUTPUT
    std::cout << std::left;
    std::for_each(freq_map.begin(), freq_map.end(), [&longest_word](std::pair<std::string, int> p) {
        std::cout << std::setw(longest_word) << p.first << " " << p.second << "\n";
    });
    std::cout.flush();
}

void handle_substitute_flag(std::vector<std::string> &text, Argument const &arg) {
    auto parsed_subs = parse_flag_by_delim(arg.parameter, '+');

    std::string old_word = parsed_subs.first;
    std::string new_word = parsed_subs.second;

    if (new_word == "") {
        throw std::logic_error("Wrong parametr type with empty substitute");
    }

    // IF THERE IS NO + SIGN old_word will be equal to new_word somehow
    else if (old_word == new_word) {
        throw std::logic_error("Wrong parametr type with no '+' for --subsitute");
    }

    std::replace(text.begin(), text.end(), old_word, new_word);
}

void handle_remove_flag(std::vector<std::string> &text, Argument const &arg) {
    text.erase(std::remove(text.begin(), text.end(), arg.parameter));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw std::logic_error(
            "Program use: a.out <path_to_text> <some-flag(s)>=<some_param(optional)>");
    }

    std::ifstream file{(argv[1])};

    if (!file.is_open()) {
        throw std::logic_error("Error opening the file!");
    }
    std::vector<std::string> text = {std::istream_iterator<std::string>(file),
                                     std::istream_iterator<std::string>()};
    int longest_word = std::max_element(text.begin(),
                                        text.end(),
                                        [](std::string const &lhs, std::string const &rhs) {
                                            return lhs.length() < rhs.length();
                                        })
                           ->length();

    // EXTRACTING ALL THE ARGS EXCEPT FOR THE FIRST 2
    std::vector<std::string> str_arguments(argv + 2, argv + argc);

    std::for_each(
        str_arguments.begin(), str_arguments.end(), [&longest_word, &text](std::string str_arg) {
            // PARSIN THE FLAG
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
                throw std::logic_error("Invalid flag: " + arg.flag);
            }
        });
}