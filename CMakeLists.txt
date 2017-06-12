cmake_minimum_required(VERSION 3.1.0)

PROJECT(nhem3)

add_executable(nhem3
    main.c
    common.c
    server.c
    client.c
)
set_property(TARGET nhem3 PROPERTY C_STANDARD 11)
