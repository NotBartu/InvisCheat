#pragma once

namespace Colors {
    // Reset
    constexpr const char* RESET = "\033[0m";

    // Standard Colors (Foreground)
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";

    // Bold Colors (Foreground)
    constexpr const char* BOLDBLACK = "\033[1m\033[30m";
    constexpr const char* BOLDRED = "\033[1m\033[31m";
    constexpr const char* BOLDGREEN = "\033[1m\033[32m";
    constexpr const char* BOLDYELLOW = "\033[1m\033[33m";
    constexpr const char* BOLDBLUE = "\033[1m\033[34m";
    constexpr const char* BOLDMAGENTA = "\033[1m\033[35m";
    constexpr const char* BOLDCYAN = "\033[1m\033[36m";
    constexpr const char* BOLDWHITE = "\033[1m\033[37m";

    // High Intensity Colors (Foreground)
    constexpr const char* BRIGHTBLACK = "\033[90m";
    constexpr const char* BRIGHTRED = "\033[91m";
    constexpr const char* BRIGHTGREEN = "\033[92m";
    constexpr const char* BRIGHTYELLOW = "\033[93m";
    constexpr const char* BRIGHTBLUE = "\033[94m";
    constexpr const char* BRIGHTMAGENTA = "\033[95m";
    constexpr const char* BRIGHTCYAN = "\033[96m";
    constexpr const char* BRIGHTWHITE = "\033[97m";

    // Bold High Intensity Colors (Foreground)
    constexpr const char* BOLDBRIGHTBLACK = "\033[1m\033[90m";
    constexpr const char* BOLDBRIGHTRED = "\033[1m\033[91m";
    constexpr const char* BOLDBRIGHTGREEN = "\033[1m\033[92m";
    constexpr const char* BOLDBRIGHTYELLOW = "\033[1m\033[93m";
    constexpr const char* BOLDBRIGHTBLUE = "\033[1m\033[94m";
    constexpr const char* BOLDBRIGHTMAGENTA = "\033[1m\033[95m";
    constexpr const char* BOLDBRIGHTCYAN = "\033[1m\033[96m";
    constexpr const char* BOLDBRIGHTWHITE = "\033[1m\033[97m";

    // Background Colors
    constexpr const char* BGBLACK = "\033[40m";
    constexpr const char* BGRED = "\033[41m";
    constexpr const char* BGGREEN = "\033[42m";
    constexpr const char* BGYELLOW = "\033[43m";
    constexpr const char* BGBLUE = "\033[44m";
    constexpr const char* BGMAGENTA = "\033[45m";
    constexpr const char* BGCYAN = "\033[46m";
    constexpr const char* BGWHITE = "\033[47m";

    // Bright Background Colors
    constexpr const char* BGBRIGHTBLACK = "\033[100m";
    constexpr const char* BGBRIGHTRED = "\033[101m";
    constexpr const char* BGBRIGHTGREEN = "\033[102m";
    constexpr const char* BGBRIGHTYELLOW = "\033[103m";
    constexpr const char* BGBRIGHTBLUE = "\033[104m";
    constexpr const char* BGBRIGHTMAGENTA = "\033[105m";
    constexpr const char* BGBRIGHTCYAN = "\033[106m";
    constexpr const char* BGBRIGHTWHITE = "\033[107m";

    // Special Effects
    constexpr const char* BOLD = "\033[1m";
    constexpr const char* DIM = "\033[2m";
    constexpr const char* ITALIC = "\033[3m";
    constexpr const char* UNDERLINE = "\033[4m";
    constexpr const char* BLINK = "\033[5m";
    constexpr const char* INVERT = "\033[7m";
    constexpr const char* HIDDEN = "\033[8m";
    constexpr const char* STRIKETHROUGH = "\033[9m";
}
