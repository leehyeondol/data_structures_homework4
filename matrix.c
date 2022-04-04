#include <stdio.h>//입출력 헤더
#include <stdlib.h>//문자열 사용 함수 헤더
#include <time.h>//시간관련함수 나열

int** create_matrix(int row, int col);//행열 제작 함수
void print_matrix(int** matrix, int row, int col);//행열 출력함수
int free_matrix(int** matrix, int row, int col);//메모리 해제 함수
int fill_data(int** matrix, int row, int col);//행열 채우기함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);//행열 덧셈
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//행열 뺄셈
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);//전치행열 구하기
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);//행열 곱셈

int main()//메인부분
{
    char command; //char형 변수 생성
    printf("[----- [Lee hyeondo]  [2019038085] -----]\n");// 이름 학번 출력 

	int row, col;// 행열 변수 생성
	srand(time(NULL));//난수 생성

	printf("Input row and col : ");//행열 입력하세요 출력
	scanf("%d %d", &row, &col);//행열 변수 입력받음
    int** matrix_a = create_matrix(row, col);//이중포인터** matrix_a에 create_matrix(row, col)함수 받아서 입력
	int** matrix_b = create_matrix(row, col);//이중포인터** matrix_b에 create_matrix(row, col)함수 받아서 입력
    int** matrix_a_t = create_matrix(col, row);//이중포인터** matrix_a_t에 create_matrix(row, col)함수 받아서 입력

	printf("Matrix Created.\n");//Matrix Created 출력

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}//만약 행열 a가 0이거나 b가 0이면 리턴-1 

	do{//do while반복문
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");//선택할 버튼 입력받을 수 있도록 Command =출력
		scanf(" %c", &command);//Command 입력받음

		switch(command) {//switch반복문
		case 'z': case 'Z'://커멘드가 z나 Z라면
		    printf("Matrix Initialized\n");//Matrix Initialized출력
			fill_data(matrix_a, row, col);//행열 a의 행열과 행의 갯수, 열의갯수를 인자로한 fill_data함수 이용
			fill_data(matrix_b, row, col);//행열 b의 행열과 행의 갯수, 열의갯수를 인자로한 fill_data함수 이용
			break;
        case 'p': case 'P'://p 나 P라면
            printf("Print matrix\n");//Print matrix출력
            printf("matrix_a\n");//matrix_a출력
			print_matrix(matrix_a, row, col);//a의 행열과 행의 갯수, 열의갯수를 인자로한 print_matrix함수 이용
			printf("matrix_b\n");//matrix_b출력
			print_matrix(matrix_b, row, col);//b의 행열과 행의 갯수, 열의갯수를 인자로한 print_matrix함수 이용
			break;
        case 'a': case 'A'://a 나 A 라면
			printf("Add two matrices\n");//Add two matrices 출력
			addition_matrix(matrix_a, matrix_b, row, col);//행열 a와b를 addition_matrix이용하여 더해줌
			break;
        case 's': case 'S'://s 나 S 라면
			printf("Subtract two matrices \n");//Subtract two matrices 출력
            subtraction_matrix(matrix_a, matrix_b, row, col);//행열 a와 b를 subtraction_matrix함수 이용하여 빼줌
			break;
        case 't': case 'T'://t 나 T라면
			printf("Transpose matrix_a \n");//Transpose matrix_a 출력
			printf("matrix_a\n");//matrix_a 출력
            transpose_matrix(matrix_a, matrix_a_t, col, row);//행열 a를 transpose_matrix함수를 이용하여 전치행열구함
            print_matrix(matrix_a_t, col, row);//print_matrix 이용하여 전치행열 출력
			break;
        case 'm': case 'M'://m 이나 M 이라면
			printf("Multiply matrix_a with transposed matrix_a \n");//Multiply matrix_a with transposed matrix_a 출력
			transpose_matrix(matrix_a, matrix_a_t, col, row);//전치행열 구함
            multiply_matrix(matrix_a, matrix_a_t, row, col);//행열 a와 전치행열의 곱
			break;
        case 'q': case 'Q'://q 거나 Q 이면
            printf("Free all matrices..\n");//Free all matrices. 출력
            free_matrix(matrix_a_t, col, row);//free_matrix함수 이용해 matrix_a_t메모리 해제
            free_matrix(matrix_a, row, col);//free_matrix함수 이용해 matrix_a메모리 해제
            free_matrix(matrix_b, row, col);//free_matrix함수 이용해 matrix_b메모리 해제
			break;
		default://아니면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//Concentration 출력
			break;
		}

	}while(command != 'q' && command != 'Q');//q 거나 Q가 아니면 다시 반복

	return 1;
}


int** create_matrix(int row, int col)//행열 생성함수
{
	
	if (row <= 0 || col <= 0) {//인자들중 하나라도 0보다 작으면
		printf("Check the size of row and col!\n");//Check the size of row and col!출력
		return NULL;//리턴 NULL
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);//이중포인터** matrix를 동적메모리 할당
	for (int r = 0; r < row; r++) {//행 개수만큼 반복
		matrix[r] = (int*)malloc(sizeof(int) * col);//각 행마다 열생성
	}

	
	if (matrix == NULL) {//matrix가 0 이면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed 출력
		return NULL;//리턴 NULL
	}

	return matrix;//리턴 matrix
}


void print_matrix(int** matrix, int row, int col)//행열 출력 함수
{
	
	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면 
		printf("Check the size of row and col!\n");//Check the size of row and col!출력
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행 수 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++)//열 수 만큼 반복
			printf("%3d ", matrix[matrix_row][matrix_col]);//행열 출력
		printf("\n");
	}
	printf("\n");
	
	 if (matrix == NULL) {//행열이 NULL이면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed 출력
		return;
	}


	return;
}


int free_matrix(int** matrix, int row, int col)//메모리 해제 함수
{

	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면
		printf("Check the size of row and col!\n");//Check the size of row and col! 출력
		return -1;//리턴 -1
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행만큼 반복
		free(matrix[matrix_row]);//행열 메모리 해제
	}

	free(matrix);//행열 메모리 해제
	return 1;
}


int fill_data(int** matrix, int row, int col)//행열 채우기 함수
{

	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면 
		printf("Check the size of row and col!\n");//Check the size of row and col! 출력
		return -1;//리턴 -1 
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)//행만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++)//열만큼 반복
			matrix[matrix_row][matrix_col] = rand() % 20;//행열의 각 원소에 랜덤한 숫자 입력

    if (matrix == NULL) {//행열이 NULL이면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed.출력
		return -1;//리턴 -1
	}
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)//행열 더하기 함수
{
    int** matrix_sum = create_matrix(row, col);//이중포인터 ** matrix_sum에 행열 입력

	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면
		printf("Check the size of row and col!\n");//Check the size of row and col! 출력
		return -1;//리턴 -1 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++)//열만큼 반복
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}//행열의 합은 행열 a + b 

	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {//행열 a 혹은 b 혹은 행열합 중 하나라도 NULL이면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed 출력
		return -1;//리턴 -1
	}

	print_matrix(matrix_sum, row, col);//행열 합 출력
	free_matrix(matrix_sum, row, col);//행열합 메모리 해제
	return 1;
}


int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//행열 빼기 함수
{
    int** matrix_sub = create_matrix(row, col);//이중포인터 ** matrix_sub에 행열 생성
	
	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면
		printf("Check the size of row and col!\n");//Check the size of row and col! 출력
		return -1;//리턴 -1
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++)//열만큼 반복
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}//행열차는 행열 a -b
	
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {//행열 a나 b 나 행열차중 하나라도 NULL이라면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed.출력
		return -1;//리턴 -1
	}
	print_matrix(matrix_sub, row, col);//행열차 출력
	free_matrix(matrix_sub, row, col);//행열차 메모리 해제

	return 1;
}


int transpose_matrix(int** matrix, int** matrix_t, int row, int col)//전치행열 구하는 함수
{
	
	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면
		printf("Check the size of row and col!\n");//Check the size of row and col!출력
		return -1;//리턴 -1
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//행만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++)//열만큼 반복
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];//행열 t는 행열[열][행]
	}

    if (matrix == NULL || matrix_t ==NULL) {//행열 혹은 행열 t가 NULL이라면
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed.출력
		return -1;//리턴 -1
	}

	return 1;
}


int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//행열 a와 전치행열의 곱 구하는 함수
{
    int** matrix_axt = create_matrix(row, row);//이중포인터** matrix_axt에 행열 입력
	
	if (row <= 0 || col <= 0) {//행이나 열이 0보다 작으면 
		printf("Check the size of row and col!\n");//Check the size of row and col!출력
		return -1;//리턴 -1
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {//행열 a의 행만큼 반복
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {//행열 t의 행만큼 반복
			int temp = 0;//temp변수 초기화 
			for (int matrix_col = 0; matrix_col < col; matrix_col++)//열만큼 반복
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];//temp+=a[a행][열]*t[열][t행]
			matrix_axt[matrix_a_row][matrix_t_row] = temp;//matrix_axt[a행][t행] = temp
		}
	}
	
    if (matrix_t == NULL || matrix_axt ==NULL) {//행열 t나 행열axt가 NULL인경우
		printf("Memory Allocation Failed.\n");//Memory Allocation Failed.출력
		return -1;//리턴 -1
	}
	print_matrix(matrix_axt, row, row);//행열곱 출력
	free_matrix(matrix_axt, row, col);//행열곱 메모리 해제
	return 1;
}