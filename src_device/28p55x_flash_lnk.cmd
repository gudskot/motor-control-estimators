
//
// Active linker CMD configuration selected by 
// the CMD Tool global settings
//
#define FLASH
#ifdef FLASH

MEMORY
{

    RAMM0                     : origin = 0x000128, length = 0x0002D8
    RAMM1                     : origin = 0x000400, length = 0x000400
    CLATOCPURAM               : origin = 0x001480, length = 0x000080
    CPUTOCLARAM               : origin = 0x001500, length = 0x000080
    CLATODMARAM               : origin = 0x001680, length = 0x000080
    DMATOCLARAM               : origin = 0x001700, length = 0x000080
    RAMLS8_CLA                : origin = 0x004000, length = 0x002000
    RAMLS9_CLA                : origin = 0x006000, length = 0x002000
    RAMLS0                    : origin = 0x008000, length = 0x000800
    RAMLS1                    : origin = 0x008800, length = 0x000800
    RAMLS2                    : origin = 0x009000, length = 0x000800
    RAMLS3                    : origin = 0x009800, length = 0x000800
    RAMLS4                    : origin = 0x00A000, length = 0x000800
    RAMLS5                    : origin = 0x00A800, length = 0x000800
    RAMLS6                    : origin = 0x00B000, length = 0x000800
    RAMLS7                    : origin = 0x00B800, length = 0x000800
    RAMGS0                    : origin = 0x00C000, length = 0x002000
    RAMGS1                    : origin = 0x00E000, length = 0x002000
    RAMGS2                    : origin = 0x010000, length = 0x002000
    RAMGS3                    : origin = 0x012000, length = 0x002000
    RAMLS8                    : origin = 0x014000, length = 0x002000
    RAMLS9                    : origin = 0x016000, length = 0x002000
    FLASH_BANK0               : origin = 0x080000, length = 0x020000
    FLASH_BANK1               : origin = 0x0A0000, length = 0x020000
    FLASH_BANK2               : origin = 0x0C0000, length = 0x020000
    FLASH_BANK3               : origin = 0x0E0000, length = 0x020000
    FLASH_BANK4               : origin = 0x100000, length = 0x008000
    RESET                     : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
    //
    // C28x Sections
    //
    .reset               : >  RESET, TYPE = DSECT /* not used, */
    codestart            : >  0x080000
    .text                : >> FLASH_BANK0 | FLASH_BANK1,
                              ALIGN(8)
    .binit               : >  FLASH_BANK0,
                              ALIGN(8)
    .ovly                : >  FLASH_BANK0,
                              ALIGN(8)
    .cinit               : >  FLASH_BANK0,
                              ALIGN(8)
    .stack               : >  RAMM1
    .init_array          : >  FLASH_BANK0,
                              ALIGN(8)
    .bss                 : >  RAMLS5
    .const               : >  FLASH_BANK0,
                              ALIGN(8)
    .data                : >> RAMGS0 | RAMGS1 | RAMGS2 | RAMGS3 | RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4 | RAMLS5 | RAMLS6 | RAMLS7 | RAMLS9 | RAMM0 | RAMM1
    .switch              : >  FLASH_BANK0,
                              ALIGN(8)
    .sysmem              : >  RAMLS4

    //
    // User Sections
    //
    ctrlfuncs {  }            LOAD >  FLASH_BANK0,
                              RUN  >  RAMLS9,
                              TABLE(BINIT),
                              LOAD_START(loadStart_ctrlfuncs),
                              LOAD_END(loadEnd_ctrlfuncs),
                              LOAD_SIZE(loadSize_ctrlfuncs),
                              RUN_START(runStart_ctrlfuncs),
                              RUN_END(runEnd_ctrlfuncs),
                              RUN_SIZE(runSize_ctrlfuncs),
                              ALIGN(8)
    .TI.ramfunc          :    LOAD > FLASH_BANK0 | FLASH_BANK1,
                              RUN  >  RAMLS8,
                              LOAD_START(RamfuncsLoadStart),
                              LOAD_END(RamfuncsLoadEnd),
                              LOAD_SIZE(RamfuncsLoadSize),
                              RUN_START(RamfuncsRunStart),
                              RUN_END(RamfuncsRunEnd),
                              RUN_SIZE(RamfuncsRunSize),
                              ALIGN(8)
    sys_data { *(sys_data) }    >  RAMLS1,
                              LOAD_START(loadStart_sys_data),
                              LOAD_END(loadEnd_sys_data),
                              LOAD_SIZE(loadSize_sys_data)
    user_data { *(user_data) }    >  RAMM1,
                              LOAD_START(loadStart_user_data),
                              LOAD_END(loadEnd_user_data),
                              LOAD_SIZE(loadSize_user_data)
    ptr_data { *(ptr_data) }    >  RAMM0,
                              LOAD_START(loadStart_ptr_data),
                              LOAD_END(loadEnd_ptr_data),
                              LOAD_SIZE(loadSize_ptr_data)
    foc_data { *(foc_data) }    >  RAMLS1,
                              LOAD_START(loadStart_foc_data),
                              LOAD_END(loadEnd_foc_data),
                              LOAD_SIZE(loadSize_foc_data)
    ctrl_data { *(ctrl_data) }    >  RAMLS2,
                              LOAD_START(loadStart_ctrl_data),
                              LOAD_END(loadEnd_ctrl_data),
                              LOAD_SIZE(loadSize_ctrl_data)
    hal_data { *(hal_data) }    >  RAMM1,
                              LOAD_START(loadStart_hal_data),
                              LOAD_END(loadEnd_hal_data),
                              LOAD_SIZE(loadSize_hal_data)
    est_data {  }          >  RAMLS1,
                              LOAD_START(loadStart_est_data),
                              LOAD_END(loadEnd_est_data),
                              LOAD_SIZE(loadSize_est_data)
    SFRA_F32_Data {  }     >  RAMLS1,
                              LOAD_START(loadStart_SFRA_F32_Data),
                              LOAD_END(loadEnd_SFRA_F32_Data),
                              LOAD_SIZE(loadSize_SFRA_F32_Data)
    datalog_data {  }      >  RAMLS1,
                              LOAD_START(loadStart_datalog_data),
                              LOAD_END(loadEnd_datalog_data),
                              LOAD_SIZE(loadSize_datalog_data)

}

#endif

/*
//===========================================================================
// End of file.
//===========================================================================
*/
