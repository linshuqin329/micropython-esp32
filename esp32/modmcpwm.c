

const mp_obj_type_t machine_mcpwm_capture_type;

typedef struct {
    mp_obj_base_t base;


} mmcpwm_capture_obj_t;

STATIC mp_obj_t mmcpwm_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
        const mp_obj_t *args) {
    //FIXME
}

// MCPWM Module

STATIC const mp_rom_map_elem_t mp_module_mcpwm_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_Capture), MP_ROM_PTR(&machine_mcpwm_capture_type) },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_mcpwm_globals, mp_module_mcpwm_globals_table);

const mp_obj_type_t mp_module_mcpwm = {
    { &mp_type_module },
    .globals = (mp_obj_t)&mp_module_mcpwm_globals,
};

// Capture objects

STATIC const mp_rom_map_elem_t mmcpwm_capture_locals_dict_table[] = {
    //{ MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mmcpwm_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_WIDTH_12BIT), MP_ROM_INT(ADC_WIDTH_12Bit) },
};

STATIC MP_DEFINE_CONST_DICT(mmcpwm_capture_locals_dict, mmcpwm_capture_locals_dict_table);
const mp_obj_type_t machine_mcpwm_capture_type = {
    { &mp_type_type },
    .name = MP_QSTR_Capture,
    .print = mmcpwm_capture_print,
    .make_new = mmcpwm_capture_make_new,
    .locals_dict = (mp_obj_t)&mmcpwm_capture_locals_dict,
};
