#include <stdio.h>
#include <tools.h>

int main() {
    hello();
    printf("%s\n", get_time_string(get_current_time()));
    printf("%ld\n", get_timestamp_by_time(get_time_by_string(get_time_string(get_current_time()))));
    printf("%ld\n", get_timestamp_by_time(get_time_by_timestamp(get_timestamp_by_time(get_current_time()))));
    printf("%ld\n", get_timestamp_by_time(get_current_time()));
    return 0;
}
