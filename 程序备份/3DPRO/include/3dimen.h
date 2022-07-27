#ifndef __3DIMEN__
#define __3DIMEN__

typedef struct
{
	double *originDotID[4];
	//��ƽ��������ĸ���(��ʼ) 
	double *finalDotID[4];
	//��ƽ��������ĸ���(����) 
	double coffiecient[3];
	//ƽ��ϵ������������ 
} planeInfo;
//����ƽ����Ϣ 

typedef struct
{
	double centrePosition[3];
	//��������������λ��
	planeInfo planeInformation[6];
	//����ƽ����Ϣ 
	double originCoordinate[8][4];
	double finalCoordinate[8][4];
	//���ո�������λ�þ���
	double length;
	double width;
	double height;
	double vector[3];
} bodyInfo;
//������������Ϣ 

typedef struct
{
	double u0, u1, u2;
	double V[4];
	//�۲��������� 
	double focusPoint[3];
	//ע�ӵ� 
    double uAxis[4];
	//u��
    double nAxis[4];
	//n�� ��Զָ����������ϵԭ�� 
    double vAxis[4];
	//v�� ��Զ��ֱ��u���n������ƽ�� 
    double eye[4];
	//�۲�����ϵԭ������������ϵ�е�λ�� 
    double change[4][4];
	//�ӽǱ任����
	double maganification;
	//������Ŵ��� 
} coordinateSystem;
//

double DotMultiply(double a[], double b[]);
//��������� 

void CoordinateChange(double a[], double b[][4], double c[]);
//�������������ϵ��Ϊ�۲�����ϵ

void ConnectDots(bodyInfo *body, coordinateSystem *coordinate, int color);
//����ͶӰ��ͼ�еĸ��� 

void ChangeMatrixInit(double change[][4]); 
//�任�����ʼ�� 

void VectorSet(double target[], double a, double b, double c, double d);
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

planeInfo PlaneInfoInit(double *originA, double *originB, double *originC, double *originD, double *finalA, double *finalB, double *finalC, double *finalD);
//����ƽ����Ϣ��ʼ�� 

void BodyInfoInit(bodyInfo *body, double length, double width, double height, double cenX, double cenY, double cenZ, double vecX, double vecY, double vecZ);
//������������Ϣ��ʼ�� 

void DrawPlane(planeInfo *plane, coordinateSystem *coordinate, int color);
//��ƽ�� 

void FocusChange(void *coordinate, void *key);
//�ӽ�ע�ӵ�任(ƽ��) 

void ZoomInAndOut(void *coordinate, void *key);
//�������� 

void Translation(bodyInfo *body, coordinateSystem *coordinate);
//����ƽ�� 

#endif 
