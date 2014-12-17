#define LOG_OPTION_SIZE 10

#define LOG_REGISTERS         1
#define LOG_PROCESSOR_STATUS  2
#define LOG_NEW_INSTRUCTIONS  4
#define LOG_NEW_DATA          8
#define LOG_TO_THE_LEFT      16
#define LOG_FRAME_NUMBER     32
#define LOG_MESSAGES         64
#define LOG_BREAKPOINTS     128
#define LOG_SYMBOLIC        256
#define LOG_CODE_TABBING    512

#define LOG_LINE_MAX_LEN 150
// Frame number - 7+1 symbols
// AXYS state - 20
// Processor status - 11
// Tabs - 31
// Address - 6
// Data - 10
// Disassembly - 63
// EOL (/0) - 1
// ------------------------
// 128 symbols total
#define LOG_AXYSTATE_MAX_LEN 21
#define LOG_PROCSTATUS_MAX_LEN 12
#define LOG_TABS_MASK 31
#define LOG_ADDRESS_MAX_LEN 7
#define LOG_DATA_MAX_LEN 11
#define LOG_DISASSEMBLY_MAX_LEN 64

extern HWND hTracer;
extern int log_update_window;
extern volatile int logtofile, logging;
extern int logging_options;
extern bool log_old_emu_paused;

void EnableTracerMenuItems(void);
void LogInstruction(void);
void DoTracer();
void UpdateLogWindow(void);
void OutputLogLine(const char *str, bool add_newline = true);
