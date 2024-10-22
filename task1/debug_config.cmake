set(MY_DEBUG_FLAGS
    -D_DEBUG
    -ggdb3
    -O0
    -Wall
    -Wextra
    -Weffc++
    -Wmissing-declarations
    -Wcast-align
    -Wcast-qual
    -Wchar-subscripts
    -Wconversion
    -Wempty-body
    -Wfloat-equal
    -Wformat-security
    -Winline
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wpacked
    -Wpointer-arith
    -Winit-self
    -Wredundant-decls
    -Wshadow
    -Wsign-conversion
    -Wsign-promo
    -Wstrict-overflow=2
    -Wsuggest-override
    -Wswitch-default
    -Wswitch-enum
    -Wundef
    -Wunreachable-code
    -Wunused
    -Wvariadic-macros
    -Wstack-protector
    -fsized-deallocation
    -fstack-protector
    -fstrict-overflow
    -fno-omit-frame-pointer
    -Wlarger-than=8192
    -fPIE
    -Werror=vla
    -fsanitize=alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
)

set(ASAN_FLAG -fsanitize=address)
set(TSAN_FLAG -fsanitize=thread)
set(MSAN_FLAG -fsanitize=memory)
