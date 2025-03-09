#pragma once

namespace Colors {
    // Reset
    constexpr const char* RESET = "\033[0m";

    namespace Foreground {
        namespace Standart {
            constexpr const char* BLACK = "\033[30m";
            constexpr const char* RED = "\033[31m";
            constexpr const char* GREEN = "\033[32m";
            constexpr const char* YELLOW = "\033[33m";
            constexpr const char* BLUE = "\033[34m";
            constexpr const char* MAGENTA = "\033[35m";
            constexpr const char* CYAN = "\033[36m";
            constexpr const char* WHITE = "\033[37m";
        }
        namespace Bold {
            constexpr const char* BLACK = "\033[1m\033[30m";
            constexpr const char* RED = "\033[1m\033[31m";
            constexpr const char* GREEN = "\033[1m\033[32m";
            constexpr const char* YELLOW = "\033[1m\033[33m";
            constexpr const char* BLUE = "\033[1m\033[34m";
            constexpr const char* MAGENTA = "\033[1m\033[35m";
            constexpr const char* CYAN = "\033[1m\033[36m";
            constexpr const char* WHITE = "\033[1m\033[37m";
        }
        namespace Bright {
            constexpr const char* BLACK = "\033[90m";
            constexpr const char* RED = "\033[91m";
            constexpr const char* GREEN = "\033[92m";
            constexpr const char* YELLOW = "\033[93m";
            constexpr const char* BLUE = "\033[94m";
            constexpr const char* MAGENTA = "\033[95m";
            constexpr const char* CYAN = "\033[96m";
            constexpr const char* WHITE = "\033[97m";
        }
        namespace BoldBright {
            constexpr const char* BLACK = "\033[1m\033[90m";
            constexpr const char* RED = "\033[1m\033[91m";
            constexpr const char* GREEN = "\033[1m\033[92m";
            constexpr const char* YELLOW = "\033[1m\033[93m";
            constexpr const char* BLUE = "\033[1m\033[94m";
            constexpr const char* MAGENTA = "\033[1m\033[95m";
            constexpr const char* CYAN = "\033[1m\033[96m";
            constexpr const char* WHITE = "\033[1m\033[97m";
        }
    }
    namespace Background {
        namespace Standart {
            constexpr const char* BLACK = "\033[40m";
            constexpr const char* RED = "\033[41m";
            constexpr const char* GREEN = "\033[42m";
            constexpr const char* YELLOW = "\033[43m";
            constexpr const char* BLUE = "\033[44m";
            constexpr const char* MAGENTA = "\033[45m";
            constexpr const char* CYAN = "\033[46m";
            constexpr const char* WHITE = "\033[47m";
        }
        namespace  {
            constexpr const char* BLACK = "\033[100m";
            constexpr const char* RED = "\033[101m";
            constexpr const char* GREEN = "\033[102m";
            constexpr const char* YELLOW = "\033[103m";
            constexpr const char* BLUE = "\033[104m";
            constexpr const char* MAGENTA = "\033[105m";
            constexpr const char* CYAN = "\033[106m";
            constexpr const char* WHITE = "\033[107m";
        }
    }
    namespace Special {
        constexpr const char* BOLD = "\033[1m";
        constexpr const char* DIM = "\033[2m";
        constexpr const char* ITALIC = "\033[3m";
        constexpr const char* UNDERLINE = "\033[4m";
        constexpr const char* BLINK = "\033[5m";
        constexpr const char* INVERT = "\033[7m";
        constexpr const char* HIDDEN = "\033[8m";
        constexpr const char* STRIKETHROUGH = "\033[9m";
    }
}
