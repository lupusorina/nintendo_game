
@{{BLOCK(ufo)

@=======================================================================
@
@	ufo, 64x32@8, 
@	Transparent color : FF,FF,FF
@	+ palette 256 entries, not compressed
@	+ 32 tiles not compressed
@	Total size: 512 + 2048 = 2560
@
@	Time-stamp: 2017-01-25, 14:42:04
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global ufoTiles		@ 2048 unsigned chars
ufoTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x01010000,0x01010000,0x1F090101,0x15653C01,0x708C079C
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x01010101,0x4B010101,0x6D1C041F,0x9824935A,0x4C74A28D,0x623F4782
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x15010100,0x01000000,0x07881F1F
	.word 0x1FA00100,0x3F3D7407,0x91731F1F,0x623F5C72,0x6D758905,0x681C680B,0x400E6254,0x51703E87
	.word 0x00000000,0x01010101,0x01010101,0x1F090101,0x5A041F15,0x169D5524,0x47388D10,0x1B0F2808
	.word 0x4D543F47,0x9F41522F,0x48622D47,0x48483333,0x787D681C,0x1E137C75,0x3B965397,0x79661079

	.word 0x01010101,0x01010101,0x1F343434,0x1F091F1F,0x164C4C4C,0x89641647,0x52414252,0x332F310A
	.word 0x4141529F,0x4D4131A5,0x21622828,0x21213F77,0x1E755A13,0x581E5A5A,0x79966666,0x85664F66
	.word 0x00000000,0x00000000,0x00010109,0x00000000,0x6F096D9E,0x00000000,0x04124C3F,0x0000018F
	.word 0x2047334D,0x00010923,0x5C4E4848,0x5F4B8E6A,0x1C68586D,0x166E750B,0x86700C85,0x4D288274
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x01010101,0x01010101,0x64477171,0x631105A4,0x41525252,0x3F540F4D
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000101,0x00000000,0x01831EA3,0x00010101,0x6A744C47,0x01010D60

	.word 0x4B150901,0x375C1113,0x50576501,0x4C81562C,0x097E0100,0x9C431509,0x00000000,0x01010101
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x33283317,0x414A3333,0x5462213F,0x4D335454,0x30841095,0x474C8069,0x1F140101,0x1E1C3434
	.word 0x00000000,0x013A0000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x48284141,0x36999948,0x4D414141,0x33331B4D,0x4D33333F,0x41334D4D,0x4C677A02,0x494D3354
	.word 0x2B1F4301,0x2F2F324C,0x1F010000,0x47640384,0x01000000,0x1F1F098B,0x00000000,0x01010000
	.word 0x2E2E6767,0x6E636E6E,0x713F6254,0x47474747,0x32492F4D,0x323F5454,0x52319A52,0x2F32332F
	.word 0x52495241,0x41414D41,0x47474716,0x82474721,0x236C0434,0x2A4B5E23,0x01010101,0x01010101

	.word 0x6E61616E,0x6B6E9B6E,0x47474747,0x62473F3F,0x2F4D4D54,0x0F0F4D2F,0x52522F49,0x1B454152
	.word 0x52525241,0x1B4D4152,0x3D3D4747,0x7F0E1616,0x34358A35,0x091F3434,0x01010101,0x00010101
	.word 0x54991D36,0x33334448,0x41333328,0x540F4141,0x4D45414D,0x4C476254,0x624D4118,0x017C9429
	.word 0x59444D1B,0x01018A76,0x25926464,0x00002743,0x90091F09,0x00000101,0x00000000,0x00000000
	.word 0x41415249,0x41414141,0x3F623954,0x21213F3F,0x2B6A5B19,0x5D882610,0x01010101,0x01010101
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x304C2833,0x01017B4F,0x1A05A147,0x01014622,0x1F1F1F06,0x00010101,0x00000101,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global ufoPal		@ 512 unsigned chars
ufoPal:
	.hword 0x7FFF,0x0000,0x1161,0x2625,0x0080,0x2626,0x0CC1,0x1D85
	.hword 0x2A86,0x0020,0x26A2,0x00E0,0x25C5,0x14C4,0x2E88,0x26A5
	.hword 0x1963,0x1DC3,0x2A29,0x0D20,0x0880,0x0460,0x2E87,0x2684
	.hword 0x22C4,0x2E89,0x2A08,0x26C5,0x00A0,0x1A02,0x0900,0x0040
	.hword 0x2E68,0x2EC7,0x1945,0x1102,0x19A3,0x21C5,0x1122,0x0C63
	.hword 0x2AC6,0x2646,0x08A0,0x1DA5,0x364A,0x2AA7,0x11A1,0x2AC4
	.hword 0x2606,0x2AC3,0x2AA4,0x2AC5,0x0060,0x04A0,0x1E03,0x2664
	.hword 0x3288,0x2A85,0x18C6,0x1564,0x0421,0x32A7,0x2E47,0x2EA6

	.hword 0x32A9,0x26C4,0x22A3,0x0CC2,0x2EC5,0x22A4,0x08A2,0x2EA7
	.hword 0x2EC6,0x26A3,0x2AE5,0x0480,0x32A8,0x26A4,0x2EA5,0x1965
	.hword 0x2DC9,0x25C7,0x26C3,0x21A7,0x2AA5,0x1DE5,0x368A,0x1905
	.hword 0x04C0,0x36A8,0x0D21,0x2A48,0x2645,0x08C0,0x0CE2,0x0882
	.hword 0x1D66,0x11A2,0x2AA6,0x1181,0x2A66,0x0441,0x1964,0x1E04
	.hword 0x00C0,0x2A27,0x25E7,0x1DE3,0x1103,0x04E0,0x15A2,0x10C5
	.hword 0x2E28,0x32C7,0x2205,0x0481,0x3289,0x0920,0x1543,0x32C6
	.hword 0x0D41,0x1984,0x19C3,0x0CE3,0x0D40,0x0500,0x18E6,0x2A67

	.hword 0x2E67,0x36A9,0x2EA8,0x08C2,0x21A5,0x25C6,0x3269,0x3689
	.hword 0x0CE1,0x1DE4,0x08A1,0x0861,0x2E08,0x2E48,0x08C1,0x0883
	.hword 0x0881,0x1D86,0x2A25,0x1562,0x1182,0x1523,0x1985,0x25C8
	.hword 0x1DC4,0x2665,0x2AE3,0x15A1,0x1503,0x2A47,0x21E5,0x22C3
	.hword 0x14C5,0x36C9,0x2E69,0x1561,0x2A46,0x26C2,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(ufo)
