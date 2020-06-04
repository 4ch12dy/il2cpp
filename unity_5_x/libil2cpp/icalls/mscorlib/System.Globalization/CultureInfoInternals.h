#pragma once

#include <stdint.h>

#if !NET_4_0
#define NUM_DAYS 7
#define NUM_MONTHS 13
#define GROUP_SIZE 5
#define NUM_OPT_CALS 5

#define NUM_SHORT_DATE_PATTERNS 14
#define NUM_LONG_DATE_PATTERNS 8
#define NUM_SHORT_TIME_PATTERNS 11
#define NUM_LONG_TIME_PATTERNS 10

#else

#define NUM_DAYS 7
#define NUM_MONTHS 13
#define GROUP_SIZE 2
#define NUM_OPT_CALS 4

#define NUM_SHORT_DATE_PATTERNS 14
#define NUM_LONG_DATE_PATTERNS 10
#define NUM_SHORT_TIME_PATTERNS 12
#define NUM_LONG_TIME_PATTERNS 9
#define NUM_YEAR_MONTH_PATTERNS 8

#endif

#define idx2string(idx) (locale_strings + (idx))

#if !NET_4_0
struct DateTimeFormatEntry
{
    const uint16_t full_date_time_pattern;
    const uint16_t long_date_pattern;
    const uint16_t short_date_pattern;
    const uint16_t long_time_pattern;
    const uint16_t short_time_pattern;
    const uint16_t year_month_pattern;
    const uint16_t month_day_pattern;

    const uint16_t am_designator;
    const uint16_t pm_designator;

    const uint16_t day_names[NUM_DAYS];
    const uint16_t abbreviated_day_names[NUM_DAYS];
    const uint16_t month_names[NUM_MONTHS];
    const uint16_t abbreviated_month_names[NUM_MONTHS];

    int8_t calendar_week_rule;
    int8_t first_day_of_week;

    const uint16_t date_separator;
    const uint16_t time_separator;

    const uint16_t short_date_patterns[NUM_SHORT_DATE_PATTERNS];
    const uint16_t long_date_patterns[NUM_LONG_DATE_PATTERNS];
    const uint16_t short_time_patterns[NUM_SHORT_TIME_PATTERNS];
    const uint16_t long_time_patterns[NUM_LONG_TIME_PATTERNS];
};
#else
struct DateTimeFormatEntry
{
    const uint16_t month_day_pattern;
    const uint16_t am_designator;
    const uint16_t pm_designator;

    const uint16_t day_names[NUM_DAYS];
    const uint16_t abbreviated_day_names[NUM_DAYS];
    const uint16_t shortest_day_names[NUM_DAYS];
    const uint16_t month_names[NUM_MONTHS];
    const uint16_t month_genitive_names[NUM_MONTHS];
    const uint16_t abbreviated_month_names[NUM_MONTHS];
    const uint16_t abbreviated_month_genitive_names[NUM_MONTHS];

    const int8_t calendar_week_rule;
    const int8_t first_day_of_week;

    const uint16_t date_separator;
    const uint16_t time_separator;

    const uint16_t short_date_patterns[NUM_SHORT_DATE_PATTERNS];
    const uint16_t long_date_patterns[NUM_LONG_DATE_PATTERNS];
    const uint16_t short_time_patterns[NUM_SHORT_TIME_PATTERNS];
    const uint16_t long_time_patterns[NUM_LONG_TIME_PATTERNS];
    const uint16_t year_month_patterns[NUM_YEAR_MONTH_PATTERNS];
};
#endif

struct NumberFormatEntry
{
    const uint16_t currency_decimal_separator;
    const uint16_t currency_group_separator;
#if !NET_4_0
    const uint16_t percent_decimal_separator;
    const uint16_t percent_group_separator;
#endif
    const uint16_t number_decimal_separator;
    const uint16_t number_group_separator;

    const uint16_t currency_symbol;
    const uint16_t percent_symbol;
    const uint16_t nan_symbol;
    const uint16_t per_mille_symbol;
    const uint16_t negative_infinity_symbol;
    const uint16_t positive_infinity_symbol;

    const uint16_t negative_sign;
    const uint16_t positive_sign;

    int8_t currency_negative_pattern;
    int8_t currency_positive_pattern;
    int8_t percent_negative_pattern;
    int8_t percent_positive_pattern;
    int8_t number_negative_pattern;

    int8_t currency_decimal_digits;
#if !NET_4_0
    int8_t percent_decimal_digits;
#endif
    int8_t number_decimal_digits;

    const int currency_group_sizes[GROUP_SIZE];
#if !NET_4_0
    const int percent_group_sizes[GROUP_SIZE];
#endif
    const int number_group_sizes[GROUP_SIZE];
};

struct TextInfoEntry
{
    /*const*/ int ansi;
    /*const*/ int ebcdic;
    /*const*/ int mac;
    /*const*/ int oem;
#if NET_4_0
    /*const*/ bool is_right_to_left;
#endif
    /*const*/ char list_sep;
};


#if !NET_4_0

struct CultureInfoEntry
{
    int16_t lcid;
    int16_t parent_lcid;
    int16_t specific_lcid;
    int16_t region_entry_index;
    /*const*/ uint16_t name;
    /*const*/ uint16_t icu_name;
    /*const*/ uint16_t englishname;
    /*const*/ uint16_t displayname;
    /*const*/ uint16_t nativename;
    /*const*/ uint16_t win3lang;
    /*const*/ uint16_t iso3lang;
    /*const*/ uint16_t iso2lang;
    /*const*/ uint16_t territory;

    int calendar_data[NUM_OPT_CALS];

    int16_t datetime_format_index;
    int16_t number_format_index;

    TextInfoEntry text_info;
};

#else

struct CultureInfoEntry
{
    int16_t lcid;
    int16_t parent_lcid;
    int16_t calendar_type;
    int16_t region_entry_index;
    /*const*/ uint16_t name;
    /*const*/ uint16_t englishname;
    /*const*/ uint16_t nativename;
    /*const*/ uint16_t win3lang;
    /*const*/ uint16_t iso3lang;
    /*const*/ uint16_t iso2lang;
    /*const*/ uint16_t territory;
    /*const*/ uint16_t native_calendar_names[NUM_OPT_CALS];

    int16_t datetime_format_index;
    int16_t number_format_index;

    TextInfoEntry text_info;
};

#endif

struct CultureInfoNameEntry
{
    const uint16_t name;
    int16_t culture_entry_index;
};

#if !NET_4_0
struct RegionInfoEntry
{
    int16_t lcid;
    int16_t region_id;
    const uint16_t iso2name;
    const uint16_t iso3name;
    const uint16_t win3name;
    const uint16_t english_name;
    const uint16_t currency_symbol;
    const uint16_t iso_currency_symbol;
    const uint16_t currency_english_name;
};
#else
struct RegionInfoEntry
{
    const int16_t geo_id;
    const uint16_t iso2name;
    const uint16_t iso3name;
    const uint16_t win3name;
    const uint16_t english_name;
    const uint16_t native_name;
    const uint16_t currency_symbol;
    const uint16_t iso_currency_symbol;
    const uint16_t currency_english_name;
    const uint16_t currency_native_name;
};
#endif

struct RegionInfoNameEntry
{
    const uint16_t name;
    int16_t region_entry_index;
};
