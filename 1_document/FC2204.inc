
;-----------------------------------------------------------------------------
;  CHIP. FH2204

.ASSEMBLY    RedWrt_FORMAT    1

.Assembly	INC_VER		6
.Assembly	ASM_FORMAT	1
.Assembly	RAM_Size	384


.Assembly	INSTRUMENT	SN8P2236
.Assembly	BIT_FILE	SN8P2236

.Assembly	OTP_BODY_SIZE	   0X1000
.Assembly	USER_ROM_SIZE	   0X0FFF

.Assembly	MASK_TEST_CODE	0x0000, 0x0000, 0x0000, 0x0000

.Assembly	PGM_TYPE	6
.Assembly	CHIP_ID		0x2600
.Assembly	command		Enable_ORG4_7, RBANK_LIMIT, GREEN_NOP_LIMIT, PCL_READ_LIMIT
.Assembly	Port_Pins	6, 8, 6, 8, 0, 3

.Assembly	USB_FIFO_Size	480, 480

; Code Option 0x3FFF
.Assembly	OPTION		0		Fix_Low
.Assembly	OPTION		1		Security	Enable	Disable
.Assembly	OPTION		2		Fcpu		Fosc/1 Fosc/2 Fosc/4 x
.Help
{
	Fcpu		: 	"Only Effective for HIGH Clock"
}
.Assembly	OPTION		4		OSC_Sel	6M_X'tal 12M_X'tal x x
.Help
{
;	IHRC_6M		:	"Internal 6M RC Oscillator"
;	IHRC_RTC	:	"Internal 6M RC Oscillator with RTC\nConnect 32768Hz crytal to XIN/XOUT"
	6M_X'tal		:	"Fosc = 12MHz, 6MHz Crystal/Resonator on XIN/XOUT"
	12M_X'tal		: 	"Fosc = 12MHz, 12MHz Crystal/Resonator on XIN/XOUT"
}
.Assembly	OPTION		6 : 7		Fix_High
.Assembly	OPTION		8		Watch_Dog	Always_On x x x x Enable x x x x Disable x x x x x
.Assembly	OPTION		12		Reset_Pin   P05 	Reset
;.Assembly	OPTION		13		Rst_Length  No 128*ILRC
.Assembly	OPTION		13		Fix_High
.Assembly	OPTION		14		Fix_Low
;.Assembly	OPTION		15		SMODE3      Disable Enable
.Assembly	OPTION		15		Fix_Low

; Code Option 0x3FFE
.Assembly	OPTION		16		Fix_Low
.Assembly	OPTION		17		Fix_High
.Assembly	OPTION		18		Fix_Low
.Assembly	OPTION		19		Fix_High
.Assembly	OPTION		20		Fix_High
.Assembly	OPTION		21		Fix_Low
.Assembly	OPTION		22		Fix_High
.Assembly	OPTION		23		Fix_Low
.Assembly	OPTION		24		Fix_Low
.Assembly	OPTION		25		Fix_High
.Assembly	OPTION		26		Fix_Low
.Assembly	OPTION		27		Fix_High
.Assembly	OPTION		28 : 31		Fix_High

; Code Option 0x3FFD
.Assembly	OPTION		32 		Fix_low
.Assembly	OPTION		33 		Fix_low
.Assembly	OPTION		34 		Fix_High
.Assembly	OPTION		35 		Fix_High
.Assembly	OPTION		36 		Fix_High
.Assembly	OPTION		37 		Fix_High
.Assembly	OPTION		38 		Fix_low
.Assembly	OPTION		39 		Fix_low
.Assembly	OPTION		40 		Fix_High
.Assembly	OPTION		41 		Fix_High
.Assembly	OPTION		42 		Fix_High
.Assembly	OPTION		43 		Fix_High
.Assembly	OPTION		44 		Fix_High
.Assembly	OPTION		45 		Fix_High
.Assembly	OPTION		46 		Fix_low
.Assembly	OPTION		47		Fix_low

; Code Option 0x3FFC
.Assembly	OPTION		48 		Fix_low
.Assembly	OPTION		49 		Fix_High
.Assembly	OPTION		50 		Fix_low
.Assembly	OPTION		51 		Fix_low
.Assembly	OPTION		52 : 63 		Fix_High

.Assembly	OPTION		2ffh



	R			EQU		82H
	Z			EQU		83H
	Y			EQU		84H
	
	PFLAG		EQU		86H
		FZ		EQU		PFLAG.0
		FDC		EQU		PFLAG.1
		FC		EQU		PFLAG.2

                FLVDF           EQU         PFLAG.5

		FNPD		EQU		PFLAG.6
		FNT0		EQU		PFLAG.7

		RBANK		EQU		87H
		FRBNKS0		EQU		RBANK.0
		FRBNKS1		EQU		RBANK.1
			
	  T0M     	EQU      0D8H
	  T0C      	EQU      0D9H
	  T0D           EQU      094H
	  T0R           EQU      095H
	  
	  T1M            EQU      0DAH
	  T1CL           EQU      0DBH
	  T1CH           EQU      0DCH
	  
	  T1NEGL         EQU     090H
	  T1NEGH         EQU     091H
	  T1POSL         EQU     092H
	  T1POSH         EQU     093H


;地址	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
;8			R	Z	Y		PFLAG	BANK								
;9	T1NEGL	T1NEGH	T1POSL	T1POSH	T0D	T0R	OPTION	PTCON	E2PCON1							
;A				P1TM	P2TM	OPACON	P2W	E2PADH	E2PADL							
;B					E2PDB		E2PCON									PEDGE
;C	P1W	P1M	P2M						INTRQ	INTEN	OSCM	RCADJ	WDTR	OPTDRV	PCL	PCH
;D		P1	P2						T0M	T0C	T1M	T1CL	T1CH			STKP
;E		P1UR	P2UR					@YZ								
;F																

          E2PCON   EQU      098H
          ;E2PCON    EQU      0b6H
          E2PDB     EQU      0B4H
          E2PADL    EQU      0A8H
          E2PADH    EQU      0A7H

      
          OPTDRV   	EQU       0CDH
          RCADJ   	EQU       0CBH
          OPACON   	EQU       0A5H
          OPTION   	EQU       096H

          PTCON   	EQU       097H
          P1TM   	EQU       0A3H
          P2TM   	EQU       0A4H
;---------------------------------------------------------
;OPTION	LVDEN	LVDS2	LVDS1	LVDS0	T1LTS	WDTP2	WDTP1	WDTP0
        FLVDEN		  EQU      OPTION.7
        FT1LTS		  EQU      OPTION.3



        FE2P_PG8BI4	          EQU      E2PCON.7

   	FE2P_CER	          EQU      E2PCON.3
   	FE2P_SER		  EQU      E2PCON.2
   	FE2P_PG		  EQU      E2PCON.1
   	FE2P_RD		  EQU      E2PCON.0
; OPACON
;	OPAE	SYNEN	IRINO	IRINT溢出时间控制	OPAI1	OPAI0  	

        FIRINO		  EQU      OPACON.5
        FSYNEN		  EQU      OPACON.6
        FOPAE		  EQU      OPACON.7
;  OPTDRV	RCADJEN	IRINT_SEL	PULLS_P2	PULLS_P1	DRVP24_1	DRVP24_0	DRVP11_0	DRVP11_0     
        FDRVP11_0		  EQU      OPTDRV.0
        FDRVP11_1		  EQU      OPTDRV.1
        FDRVP24_0		  EQU      OPTDRV.2
        FDRVP24_1		  EQU      OPTDRV.3
        FPULLS_P1		  EQU      OPTDRV.4
        FPULLS_P2		  EQU      OPTDRV.5
        FIRINT_SEL		  EQU      OPTDRV.6
        FRCADJEN		  EQU      OPTDRV.7 
;PTCON	SSEL0	DKWE	T1WDS	T1WDL	POWER	IRCON	DSEL1	DSEL0

        FDSEL0		  EQU      PTCON.0
        FDSEL1		  EQU      PTCON.1
        FIRCON		  EQU      PTCON.2
        FPOWER		  EQU      PTCON.3
        FT1WDL		  EQU      PTCON.4
        FT1WDS		  EQU      PTCON.5
        FDKWE		  EQU      PTCON.6
        FSSEL0		  EQU      PTCON.7
        
;T0M	T0TR	T0PS2	T0PS1	T0PS0	T0PT1	T0PT0	T0CS	PWMOUT      
        FPWMOUT		  EQU      T0M.0
        FT0CS		  EQU      T0M.1
        FT0PT0		  EQU      T0M.2
        FT0PT1		  EQU      T0M.3
        FT0PS0		  EQU      T0M.4
        FT0PS1		  EQU      T0M.5
        FT0PS2		  EQU      T0M.6
        FTR0		  EQU      T0M.7
        
;T1M	TR1	TP1S2	TP1S1	TP1S0	T1PT1	T1PT0	T1GN	T1TRSEL

        FT1TRSEL	  EQU      T1M.0
        FT1GN		  EQU      T1M.1
        FT1PT0		  EQU      T1M.2
        FT1PT1		  EQU      T1M.3
        FTP1S0		  EQU      T1M.4
        FTP1S1		  EQU      T1M.5
        FTP1S2		  EQU      T1M.6
        FTR1		  EQU      T1M.7



	PEDGE		EQU		0BFH		
		FP11G1		EQU		PEDGE.4
		FP11G0		EQU		PEDGE.3
		FP24G1		EQU		PEDGE.2
 		FP24G0		EQU		PEDGE.1
        P2W			EQU		0A6H
	P1W			EQU		0C0H
		FP17W	EQU		P1W.7
		FP16W	EQU		P1W.6
		FP15W	EQU		P1W.5
		FP14W	EQU		P1W.4
		FP13W	EQU		P1W.3
		FP12W	EQU		P1W.2
		FP11W	EQU		P1W.1
		FP10W	EQU		P1W.0
		
	
	P0M			EQU		0b8H

		FP03M	EQU		P0M.3
		FP02M	EQU		P0M.2
		FP01M	EQU		P0M.1
		FP00M	EQU		P0M.0	
		

	P1M			EQU		0C1H
		FP17M	EQU		P1M.7
		FP16M	EQU		P1M.6
		FP15M	EQU		P1M.5
		FP14M	EQU		P1M.4
		FP13M	EQU		P1M.3
		FP12M	EQU		P1M.2
		FP11M	EQU		P1M.1
		FP10M	EQU		P1M.0
		
	P2M			EQU		0C2H
		FP25M	EQU		P2M.5
		FP24M	EQU		P2M.4
		FP23M	EQU		P2M.3
		FP22M	EQU		P2M.2
		FP21M	EQU		P2M.1
		FP20M	EQU		P2M.0
	P3M			EQU		0C3H
                FP37M	EQU		P3M.7
		FP36M	EQU		P3M.6
		FP35M	EQU		P3M.5
		FP34M	EQU		P3M.4
		FP33M	EQU		P3M.3
		FP32M	EQU		P3M.2
		FP31M	EQU		P3M.1
		FP30M	EQU		P3M.0
	
 ; E2PIE	RBIE	T1IE	T0IE	INT1IE	INT0IE	

	INTRQ		EQU		0C8H


		FE2PIF		EQU		INTRQ.5
		FRBIF		EQU		INTRQ.4
		FT1IF		EQU		INTRQ.3
		FT0IF		EQU		INTRQ.2
		FINT1IF		EQU		INTRQ.1
		FINT0IF		EQU		INTRQ.0
	INTEN		EQU		0C9H
		FE2PIE		EQU		INTEN.5
		FRBIE		EQU		INTEN.4
		FT1IE		EQU		INTEN.3
		FT0IE		EQU		INTEN.2
		FINT1IE		EQU		INTEN.1
		FINT0IE		EQU		INTEN.0

	OSCM		EQU		0CAH
		FCPUM1	EQU		OSCM.4
		FCPUM0	EQU		OSCM.3
		FCLKMD	EQU		OSCM.2
		FSTPHX	EQU		OSCM.1

	WDTR		EQU	0CCH
		

    
	PCL			EQU		0CEH
	PCH			EQU		0CFH

	P0			EQU 	0D0H

		FP03	EQU 	P0.3
		FP02	EQU 	P0.2
		FP01	EQU 	P0.1
		FP00	EQU 	P0.0
		
	P1			EQU 	0D1H
		FP17	EQU 	P1.7
		FP16	EQU 	P1.6
		FP15	EQU 	P1.5
		FP14	EQU 	P1.4
		FP13	EQU 	P1.3
		FP12	EQU 	P1.2
		FP11	EQU 	P1.1
		FP10	EQU 	P1.0
		
	P2			EQU 	0D2H
		FP25	EQU 	P2.5
		FP24	EQU 	P2.4
		FP23	EQU 	P2.3
		FP22	EQU 	P2.2
		FP21	EQU 	P2.1
		FP20	EQU 	P2.0	
	P3			EQU 	0D3H
		FP37	EQU 	P3.7
		FP36	EQU 	P3.6	
		FP35	EQU 	P3.5
		FP34	EQU 	P3.4
		FP33	EQU 	P3.3
		FP32	EQU 	P3.2
		FP31	EQU 	P3.1
		FP30	EQU 	P3.0	
				
	
		
	


	STKP		EQU		0DFH
		FGIE	EQU		STKP.7
		FSTKPB2	EQU		STKP.2
		FSTKPB1	EQU		STKP.1
		FSTKPB0	EQU		STKP.0


    P0UR        EQU     0E0H
    P1UR        EQU     0E1H
    P2UR	EQU	0E2H
		FP24R	EQU		P2UR.4
		FP23R	EQU		P2UR.3
		FP22R	EQU		P2UR.2
		FP21R	EQU		P2UR.1
		FP20R	EQU		P2UR.0
    P3UR	EQU			0E3H

       
	@YZ			EQU		0E7H

;*******************************************************
; Clear watchdog macro. 
;  
; Total Cycle: 2
    @RST_WDT macro
           MOV  A, #0x5A
           B0MOV  WDTR, A
    endm

;******************************************************
; Sleep Mode control macro for compatibility in S8KD-2 ICE
;  
; Total Cycle: 1
    SleepMode macro          
           B0BSET      FCPUM0
    endm
;******************************************************
; Green Mode control macro for compatibility in S8KD-2 ICE
;  
; Total Cycle: 3
    GreenMode macro          
           B0BSET      FCPUM1
           NOP
           NOP
    endm
;******************************************************
; Slow Mode control macro for compatibility in S8KD-2 ICE
;  
; Total Cycle: 2
    SlowMode macro          
           B0BSET      FCLKMD
           B0BSET      FSTPHX
    endm
;******************************************************
;  Slow mode to Normal Mode control macro for compatibility in S8KD-2 ICE
;  
; Total Cycle: 5
    Slow2Normal       macro          
           B0BCLR     FSTPHX
           NOP
           NOP
           NOP
           B0BCLR     FCLKMD
    endm
;******************************************************
.TEXT
{
	//{{SONIX_OPTION_RULE
        
	ENDP
	//}}SONIX_OPTION_RULE
}
