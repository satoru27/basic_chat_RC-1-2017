cmake_minimum_required(VERSION 3.1.0)

PROJECT(TRAB_RC)

add_executable(TRAB_RC
    main.c
    client.c
    server.c
)
set_property(TARGET TRAB_RC PROPERTY C_STANDARD 11)
