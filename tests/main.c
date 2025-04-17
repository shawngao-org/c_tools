#include "tools.h"
#include "collect_test/linked_list_test.h"
#include "time_test/time_test.h"
#include "string_test/string_test.h"
#include "collect_test/stack_test.h"

int main() {
    hello();
    time_test();
    string_test();
    stack_test();
    linked_list_test();
    return 0;
}
