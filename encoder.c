#include "encoder.h"

//��� ��� ����������� ����
#define b00000011 3
#define b11010010 210
#define b11100001 225

volatile unsigned char bufEnc = 0; //����� ��������

//������� ������ ��������
//___________________________________________
unsigned char ENC_PollEncoder(void)
{
static unsigned char stateEnc; 	//������ ������������������ ��������� ��������
unsigned char tmp;  
unsigned char currentState = 0;

//��������� ��������� ������� ����������������
if (ENC_A != 0) {currentState |= (1<<0);}
if (ENC_C != 0) {currentState |= (1<<1);}

//���� ����� �����������, �� �������
tmp = stateEnc;
if (currentState == (tmp & b00000011)) return 1;

//���� �� �����, �� �������� � ��������� � ���
tmp = (tmp<<2)|currentState;
stateEnc = tmp;

//���������� ������������ ������������������
if (tmp == b11100001) bufEnc = LEFT_SPIN;
if (tmp == b11010010) bufEnc = RIGHT_SPIN;
return 0;
}

//������� ������������ �������� ������ ��������
//_____________________________________________
unsigned char ENC_GetStateEncoder(void)
{
  unsigned char tmp = bufEnc;
  bufEnc = 0;
  return tmp;
}


