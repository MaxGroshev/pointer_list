#if defined(DEBUG)
#define LIST_CHECK(condition, code_of_error)                                                             \
        if (!(condition))                                                                                \
        {                                                                                                \
            list_error (code_of_error, CUR_POS_IN_PROG);                                                 \
            return -1;                                                                                   \
        }                                                                                                \

#else
#define LIST_CHECK;

#endif
