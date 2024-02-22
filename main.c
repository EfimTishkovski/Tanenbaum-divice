/*
 * RGB_for_tiny13.c
 *
 * Created: 20.11.2023 21:11:34
 * Author : asrock
 */ 

//Управление RGB светодиодом для Attiny13A Програмный ШИМ
#define F_CPU 4800000L


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char pwm_r, pwm_g, pwm_b;

//Прерывание по переполнению таймера T0
ISR(TIM0_OVF_vect)
{
	static unsigned char pwm_counter;
	// Если значение яркости больше значения счётчика
	
	// Включаем соответствующий вывод
	
	// Красный
	if (pwm_counter < pwm_r) {PORTB |= (1 << PORTB3); } // PB3
	else {PORTB &= ~(1 << PORTB3); }                    // PB3
	
	// Зелёный
	if (pwm_counter < pwm_g){PORTB |= (1 << PORTB1); }  // PB1
	else {PORTB &= ~(1 << PORTB1); }                    // PB1
	
	// Синий
	if (pwm_counter < pwm_b){PORTB |= (1 << PORTB2); }  // PB2
	else {PORTB &= ~(1 << PORTB2); }                    // PB2
	
	// Счётчик
	pwm_counter++;
}

// Произвольный цвет
void random_lite (unsigned char reds, unsigned char greens, unsigned char blues)
{
	// Увеличение яркости
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
	_delay_ms(41000); // Задержка для свечения
	
	// Уменьшение яркости
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

// Смена цветов
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

// Функция случайного числа не реализована, код инициализации АЦП оставлен на память
// АЦП выдавал 0 постоянно, причину установить не удалось
// Полсе выноса инициализации АЦП в отдельную функцию, нарушилась работа функции rgb()
// Реализация через ADC и площадку с наводками напряжения (контакт в воздухе) взятие случайного значения
// в диапазоне размера массива с цветами
/*
Исходный вид массива с цветами
{255,0,0},      //  0 Красный
{0,255,0},      //  1 Зелёный
{0,0,255},      //  2 Синий
{255,255,255},  //  3 Белый
{255,255,0},    //  4 Жёлтый
{255,0,255},    //  5 Фуксия
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

// Иннициализация АЦП
void ACD_ini ()
{
	ADCSRA |= (1 << ADEN)                      // АЦП задействован
	|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);   // Делитель 128 частота АЦП 75кГц
	ADMUX |= (1 << REFS0)|(1 << MUX1);         // Внутреннее опорное напряжение (1.1 в), задействован ACD2 НА НОГЕ 3
}
// Случайное число 0-15
unsigned char random_ADC ()
{
	// unsigned char result = 0;
	ADCSRA |= (1 << ADSC);                  // Старт преобразования
	while((ADCSRA & (1 << ADSC)));          // Проверка окончания измерения, в бите ADSC должен быть 0
	//result = ADC;                         // Берём младшие 4 бита из ACD (10-и битное число c результатом измерения)
	return (ADC >> 7);                      // Результат в виде unsigned char 0-15 в двоичной системе (0000 - 1111)
}
*/


unsigned char color_mass [16][3] =
{
	{0,255,127},    //  7 SpringGreen
	{255,255,0},    //  4 Жёлтый
	{0,139,139},    //  9 DarkCyan
	{0,0,255},      //  2 Синий
	{123,104,238},  // 14 MediumSlateBlue
	{128,0,128},     // 15 Purple
	{199,21,133},   //  6 MediumVioletRed
	{0,191,255},    // 13 DeepSkyBlue
	{0,255,255},    //  8 Aqua
	{0,250,154},    // 11 MediumSpringGreen
	{127,255,212},  // 12 Aquamarine
	{255,0,0},    //  0 Красный
	{0,255,0},      //  1 Зелёный
	{255,0,255},   //  5 Фуксия
	{0,100,0},      // 10 DarkGreen
	{255,255,255},  //  3 Белый
};

unsigned char number_color = 0;

// Основной код
int main(void)
{
	// Порты
	DDRB = 0xFF;   // Порт В на выход
	PORTB = 0x00;  // Состояние порта
	// Таймер 0
	TCCR0B |= (1 << CS00);  // Тактирование Таймера Т0 без пред делителя
	TIMSK0 |= (1 << TOIE0); // Прерывание по переполнению
	
	sei();        // Разрешение глобальных прерываний
	
	rgb();        // Проверка при запуске
	
	while (1)
	{
		for (unsigned char i = 0; i < 16; i++)
		{
			number_color = i;
			random_lite(color_mass[number_color][0], color_mass[number_color][1], color_mass[number_color][2]); // Зажигание света на диоде
			_delay_ms(500);
		}
	}
}

