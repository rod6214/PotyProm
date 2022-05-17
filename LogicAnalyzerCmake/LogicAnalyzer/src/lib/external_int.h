/*
 * external_int.h
 *
 * Created: 5/17/2022 7:29:03 PM
 *  Author: Nelson
 */
// INT4 
extern void enable_int4(); 
extern void disable_int4();
extern int is_int4_flag();
extern void clear_int4_flag();
extern void sense_on_low_level_int4();
extern void sense_on_any_change_int4();
extern void sense_on_falling_edge_int4();
extern void sense_on_rising_edge_int4();
// INT5
extern void enable_int5(); 
extern void disable_int5();
extern int is_int5_flag();
extern void clear_int5_flag();
extern void sense_on_low_level_int5();
extern void sense_on_any_change_int5();
extern void sense_on_falling_edge_int5();
extern void sense_on_rising_edge_int5();
