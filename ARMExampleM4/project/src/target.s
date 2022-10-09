    .section .__system
    .global BOOT_OperatingSystem
BOOT_OperatingSystem:
    push {r0, lr}
    blx r0
    pop {r0, pc}
