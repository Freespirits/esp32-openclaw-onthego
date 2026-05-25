idf_component_register(
    SRCS "test_esp_mochi_node.c"
    INCLUDE_DIRS "."
    REQUIRES
        mbedtls
        nvs_flash
        esp-mochi-node
        unity
)

idf_component_get_property(esp_mochi_node_dir esp-mochi-node COMPONENT_DIR)
target_include_directories(${COMPONENT_LIB} PRIVATE "${esp_mochi_node_dir}/private_include")
