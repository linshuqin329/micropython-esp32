#include <stdio.h>
#include <string.h>

#include "esp_log.h"

#include "py/runtime.h"
#include "modmachine.h"


#include "driver/spi_master.h"

STATIC mp_obj_t spi_test(void) {

    spi_bus_config_t                bus_config;
    spi_device_interface_config_t   device_config;
    spi_device_handle_t             spi;
    spi_host_device_t               host = 1;
    int                             dma = 1;

    memset(&bus_config, 0, sizeof(spi_bus_config_t));
    memset(&device_config, 0, sizeof(spi_device_interface_config_t));

    bus_config.miso_io_num = -1;
    bus_config.mosi_io_num = 26;
    bus_config.sclk_io_num = 25;
    bus_config.quadwp_io_num = -1;
    bus_config.quadhd_io_num = -1;

    device_config.clock_speed_hz = 50000;
    device_config.mode = 0;
    device_config.spics_io_num = -1;
    device_config.queue_size = 1;
    device_config.flags = SPI_DEVICE_TXBIT_LSBFIRST | SPI_DEVICE_RXBIT_LSBFIRST;

    assert(spi_bus_initialize(host, &bus_config, dma) == ESP_OK);
    assert(spi_bus_add_device(host, &device_config, &spi) == ESP_OK);

    struct spi_transaction_t transaction = {
        .flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA,
        .length = 16,
        .tx_buffer = NULL,
        .rx_buffer = NULL,
        .tx_data = {0x04, 0x00}
    };

    printf("before first xmit\n");
    assert(spi_device_transmit(spi, &transaction) == ESP_OK);
    printf("after first xmit\n");

    assert(spi_bus_remove_device(spi) == ESP_OK);
    assert(spi_bus_free(host) == ESP_OK);

    // change things up!
    bus_config.mosi_io_num = 4;
    host = 2;
    
    assert(spi_bus_initialize(host, &bus_config, dma) == ESP_OK);
    assert(spi_bus_add_device(host, &device_config, &spi) == ESP_OK);

    printf("before second xmit\n");
    assert(spi_device_transmit(spi, &transaction) == ESP_OK);
    printf("after second xmit\n");

    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(spi_test_obj, spi_test);

STATIC const mp_rom_map_elem_t spi_test_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_test), MP_ROM_PTR(&spi_test_obj) },
};

STATIC MP_DEFINE_CONST_DICT(spi_test_locals_dict, spi_test_locals_dict_table);

const mp_obj_type_t machine_spi_test_type = {
    { &mp_type_type },
    .name = MP_QSTR_spi_test,
    .locals_dict = (mp_obj_t)&spi_test_locals_dict
};
