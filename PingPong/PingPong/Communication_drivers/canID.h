/*
 * canID.h
 *
 * Created: 09.10.2015 13:48:37
 *  Author: sverrevr
 */ 


#ifndef CANID_H_
#define CANID_H_

//id: 1*highPrio, 8*unit specify  ,2*msg
#define CANID_MCUH_MASK 0b11000000001U
#define CANID_MCUL_MASK 0b11000000011U

#define CANID_MCU_HIGHPRIO_0 0b01000000000U
#define CANID_MCU_HIGHPRIO_1 0b01000000001U

#define CANID_MCU_0 0b11000000000U
#define CANID_MCU_1 0b11000000001U
#define CANID_MCU_2 0b11000000010U
#define CANID_MCU_3 0b11000000011U




#endif /* CANID_H_ */
