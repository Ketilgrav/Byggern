/*
 * canID.h
 *
 * Created: 09.10.2015 13:48:37
 *  Author: sverrevr
 */ 


#ifndef CANID_H_
#define CANID_H_

//id: 1*highPrio, 8*unit specify  ,2*msg
#define NODE1_CANID_H_MASK 0b11000000001U
#define NODE1_CANID_L_MASK 0b11000000011U

#define NODE1_CANID_HIGHPRIO_0 0b01000000000U
#define NODE1_CANID_HIGHPRIO_1 0b01000000001U

#define NODE1_CANID_0 0b11000000000U
#define NODE1_CANID_1 0b11000000001U
#define NODE1_CANID_2 0b11000000010U
#define NODE1_CANID_3 0b11000000011U


#define NODE2_CANID_H_MASK 0b10100000001U
#define NODE2_CANID_L_MASK 0b10100000011U

#define NODE2_CANID_HIGHPRIO_0 0b00100000000U
#define NODE2_CANID_HIGHPRIO_1 0b00100000001U

#define NODE2_CANID_0 0b10100000000U
#define NODE2_CANID_1 0b10100000001U
#define NODE2_CANID_2 0b10100000010U
#define NODE2_CANID_3 0b10100000011U




#endif /* CANID_H_ */