#ifndef __3DIMEN__
#define __3DIMEN__

typedef struct
{
	//float centrePosition[3];
	float *originDotID[4];
	//��ƽ��������ĸ���(��ʼ) 
	float *finalDotID[4];
	//��ƽ��������ĸ���(����) 
	float coffiecient[3];
	//ƽ��ϵ������������ 
} planeInfo;
//����ƽ����Ϣ 

typedef struct
{
	float centrePosition[4];
	float finalCentrePosition[4];
	//��������������λ��
	planeInfo planeInformation[6];
	//����ƽ����Ϣ 
	float originCoordinate[8][4];
	float relaCoordinate[8][4];
	float finalCoordinate[8][4];
	//���ո�������λ�þ���
	float length;
	float width;
	float height;
	float angle;//��¼��ת�ĽǶ� 
} bodyInfo;
//������������Ϣ 

typedef struct
{
	float u0, u1, u2;
	float V[4];
	//�۲��������� 
	float focusPoint[3];
	//ע�ӵ� 
    float uAxis[4];
	//u��
    float nAxis[4];
	//n�� ��Զָ����������ϵԭ�� 
    float vAxis[4];
	//v�� ��Զ��ֱ��u���n������ƽ�� 
    float eye[4];
	//�۲�����ϵԭ������������ϵ�е�λ�� 
    float change[4][4];
	//�ӽǱ任����
	float maganification;
	//������Ŵ��� 
} coordinateSystem;
//

float DotMultiply(float a[], float b[]);
//��������� 

void CoordinateChange(float a[], float b[][4], float c[]);
//�������������ϵ��Ϊ�۲�����ϵ

void ConnectDots(bodyInfo *body, coordinateSystem *coordinate, int color, int lcolor);
//����ͶӰ��ͼ�еĸ��� 

void ChangeMatrixInit(float change[][4]); 
//�任�����ʼ�� 

void VectorSet(float target[], float a, float b, float c, float d);
//������ʼ��

void CoordinateInit(coordinateSystem *coordinate);
//��ά�任 

void ChangeView(void *coordinate, void *key);
//��ת�ӽ� 

void CalUVN(coordinateSystem *coordinate);
//����UVN���ᵥλ����

void GiveUnit(coordinateSystem *coordinate);
//���������õ�λ������������任���� 

void CalPlaneCoffiecient(planeInfo *planeInformation);
//�������ƽ��ϵ������ 

planeInfo PlaneInfoInit(float *originA, float *originB, float *originC, float *originD, float *finalA, float *finalB, float *finalC, float *finalD);
//����ƽ����Ϣ��ʼ�� 

void BodyInfoInit(bodyInfo *body, float length, float width, float height, float cenX, float cenY, float cenZ, float vecX, float vecY, float vecZ);
//������������Ϣ��ʼ�� 

void DrawPlane(planeInfo *plane, coordinateSystem *coordinate, int color, int lcolor);
//��ƽ�� 

void FocusChange(void *coordinate, void *key);
//�ӽ�ע�ӵ�任(ƽ��) 

void ZoomInAndOut(void *coordinate, void *key);
//�������� 

void Translation(bodyInfo *body, float finalX, float finalY, float finalZ);
//����ƽ�� 

void BodyPlaneCal(bodyInfo *body);
//�����������ƽ�淨���� 

void BodyPointCal(bodyInfo *body);
//��������������� 

void OriginBodyPointCal(bodyInfo *body);
//��������������� 

void Spin(bodyInfo *body, float angle);
//��ת����

void SpinPoint(float point[], float angle);
//��ת�� 

#endif 
