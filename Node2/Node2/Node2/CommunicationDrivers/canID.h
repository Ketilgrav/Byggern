/*
 * canID.h
 *
 * Created: 09.10.2015 13:48:37
 *  Author: sverrevr
 */ 


#ifndef CANID_H_
#define CANID_H_

//id: 1*highPrio, 8*unit specify  ,2*msg
#define CANID_MCUH_mask 0b10100000001U
#define CANID_MCUL_mask 0b10100000011U

#define CANID_MCU_HIGHPRIO_0 0b00100000000U
#define CANID_MCU_HIGHPRIO_1 0b00100000001U

#define CANID_MCU_0 0b10100000000U
#define CANID_MCU_1 0b10100000001U
#define CANID_MCU_2 0b10100000010U
#define CANID_MCU_3 0b10100000011U




#endif /* CANID_H_ */