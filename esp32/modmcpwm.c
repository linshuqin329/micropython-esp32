/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 "Eric Poulsen" <eric@zyxod.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/obj.h"
#include "py/runtime.h"

typedef struct {
    mp_obj_base_t base;


} mmcpwm_capture_obj_t;

/******************************************************************************/
// MicroPython bindings for hw_spi

STATIC void mmcpwm_capture_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {

    mmcpwm_capture_obj_t* self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "Capture(%p)", self);
}

const mp_obj_type_t machine_mcpwm_capture_type;


STATIC mp_obj_t mmcpwm_capture_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw,
        const mp_obj_t *args) {
    //FIXME
    //
    return mp_const_none;
}

// MCPWM Module

STATIC const mp_rom_map_elem_t mp_module_mcpwm_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_Capture), MP_ROM_PTR(&machine_mcpwm_capture_type) },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_mcpwm_globals, mp_module_mcpwm_globals_table);

const mp_obj_module_t mp_module_mcpwm = {
    { &mp_type_module },
    .globals = (mp_obj_t)&mp_module_mcpwm_globals,
};

// Capture objects

STATIC const mp_rom_map_elem_t mmcpwm_capture_locals_dict_table[] = {
    //{ MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mmcpwm_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_WIDTH_12BIT), MP_ROM_INT(0) },
};

STATIC MP_DEFINE_CONST_DICT(mmcpwm_capture_locals_dict, mmcpwm_capture_locals_dict_table);
const mp_obj_type_t machine_mcpwm_capture_type = {
    { &mp_type_type },
    .name = MP_QSTR_Capture,
    .print = mmcpwm_capture_print,
    .make_new = mmcpwm_capture_make_new,
    .locals_dict = (mp_obj_t)&mmcpwm_capture_locals_dict,
};
