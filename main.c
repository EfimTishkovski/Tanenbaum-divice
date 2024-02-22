/*
 * RGB_for_tiny13.c
 *
 * Created: 20.11.2023 21:11:34
 * Author : asrock
 */ 

//���������� RGB ����������� ��� Attiny13A ���������� ���
#define F_CPU 4800000L


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char pwm_r, pwm_g, pwm_b;

//���������� �� ������������ ������� T0
ISR(TIM0_OVF_vect)
{
	static unsigned char pwm_counter;
	// ���� �������� ������� ������ �������� ��������
	
	// �������� ��������������� �����
	
	// �������
	if (pwm_counter < pwm_r) {PORTB |= (1 << PORTB3); } // PB3
	else {PORTB &= ~(1 << PORTB3); }                    // PB3
	
	// ������
	if (pwm_counter < pwm_g){PORTB |= (1 << PORTB1); }  // PB1
	else {PORTB &= ~(1 << PORTB1); }                    // PB1
	
	// �����
	if (pwm_counter < pwm_b){PORTB |= (1 << PORTB2); }  // PB2
	else {PORTB &= ~(1 << PORTB2); }                    // PB2
	
	// �������
	pwm_counter++;
}

// ������������ ����
void random_lite (unsigned char reds, unsigned char greens, unsigned char blues)
{
	// ���������� �������
	for (unsigned char a = 0; a < 255; a++)
	{
		if (reds >= a) {pwm_r = a;}
		else{pwm_r = reds;}
		
		if (greens >= a) {pwm_g = a;}
		else{pwm_g = greens;}
		
		if (blues >= a) {pwm_b = a;}
		else{pwm_b = blues;}
		_delay_ms(30);
	}
	_delay_ms(41000); // �������� ��� ��������
	
	// ���������� �������
	for (unsigned char a = 255; a > 0; a--)
	{
		if (reds <= a) {pwm_r = reds;}
		else{pwm_r = a;}
		
		if (greens <= a) {pwm_g = greens;}
		else{pwm_g = a;}
		
		if (blues <= a) {pwm_b = blues;}
		else{pwm_b = a;}
		_delay_ms(30);
	}
	pwm_r = 0;
	pwm_g = 0;
	pwm_b = 0;
}

// ����� ������
void rgb ()
{
	for (unsigned char a = 0; a < 255; a++)
	{
		pwm_r = a;
		pwm_g = 255 - a;
		_delay_ms(30);
	}
	for (unsigned char a = 0; a < 255; a++)
	{
		pwm_b = a;
		pwm_r = 255 - a;
		_delay_ms(30);
	}
	for (unsigned char a = 0; a < 255; a++)
	{
		pwm_g = a;
		pwm_b = 255 - a;
		_delay_ms(30);
	}
}

// ������� ���������� ����� �� �����������, ��� ������������� ��� �������� �� ������
// ��� ������� 0 ���������, ������� ���������� �� �������
// ����� ������ ������������� ��� � ��������� �������, ���������� ������ ������� rgb()
// ���������� ����� ADC � �������� � ��������� ���������� (������� � �������) ������ ���������� ��������
// � ��������� ������� ������� � �������
/*
�������� ��� ������� � �������
{255,0,0},      //  0 �������
{0,255,0},      //  1 ������
{0,0,255},      //  2 �����
{255,255,255},  //  3 �����
{255,255,0},    //  4 Ƹ����
{255,0,255},    //  5 ������
{199,21,133},   //  6 MediumVioletRed
{0,255,127},    //  7 SpringGreen
{0,255,255},    //  8 Aqua
{0,139,139},    //  9 DarkCyan
{0,100,0},      // 10 DarkGreen
{0,250,154},    // 11 MediumSpringGreen
{127,255,212},  // 12 Aquamarine
{0,191,255},    // 13 DeepSkyBlue
{123,104,238},  // 14 MediumSlateBlue
{128,0,128}     // 15 Purple

// �������������� ���
void ACD_ini ()
{
	ADCSRA |= (1 << ADEN)                      // ��� ������������
	|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);   // �������� 128 ������� ��� 75���
	ADMUX |= (1 << REFS0)|(1 << MUX1);         // ���������� ������� ���������� (1.1 �), ������������ ACD2 �� ���� 3
}
// ��������� ����� 0-15
unsigned char random_ADC ()
{
	// unsigned char result = 0;
	ADCSRA |= (1 << ADSC);                  // ����� ��������������
	while((ADCSRA & (1 << ADSC)));          // �������� ��������� ���������, � ���� ADSC ������ ���� 0
	//result = ADC;                         // ���� ������� 4 ���� �� ACD (10-� ������ ����� c ����������� ���������)
	return (ADC >> 7);                      // ��������� � ���� unsigned char 0-15 � �������� ������� (0000 - 1111)
}
*/


unsigned char color_mass [16][3] =
{
	{0,255,127},    //  7 SpringGreen
	{255,255,0},    //  4 Ƹ����
	{0,139,139},    //  9 DarkCyan
	{0,0,255},      //  2 �����
	{123,104,238},  // 14 MediumSlateBlue
	{128,0,128},     // 15 Purple
	{199,21,133},   //  6 MediumVioletRed
	{0,191,255},    // 13 DeepSkyBlue
	{0,255,255},    //  8 Aqua
	{0,250,154},    // 11 MediumSpringGreen
	{127,255,212},  // 12 Aquamarine
	{255,0,0},    //  0 �������
	{0,255,0},      //  1 ������
	{255,0,255},   //  5 ������
	{0,100,0},      // 10 DarkGreen
	{255,255,255},  //  3 �����
};

unsigned char number_color = 0;

// �������� ���
int main(void)
{
	// �����
	DDRB = 0xFF;   // ���� � �� �����
	PORTB = 0x00;  // ��������� �����
	// ������ 0
	TCCR0B |= (1 << CS00);  // ������������ ������� �0 ��� ���� ��������
	TIMSK0 |= (1 << TOIE0); // ���������� �� ������������
	
	sei();        // ���������� ���������� ����������
	
	rgb();        // �������� ��� �������
	
	while (1)
	{
		for (unsigned char i = 0; i < 16; i++)
		{
			number_color = i;
			random_lite(color_mass[number_color][0], color_mass[number_color][1], color_mass[number_color][2]); // ��������� ����� �� �����
			_delay_ms(500);
		}
	}
}

