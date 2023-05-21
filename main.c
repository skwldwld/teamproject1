#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 일단 메뉴 선택을 만들자
 * 1. 원소 추가 void add_menu(menu* s)
 * 2. 원소 삭제(이름검색) void del_menu(menu* s,char name[],int num);
 * 3. 모든 원소 출력 void print_menu(menu* s,int num)
 * 4. 원소 수정 void search_menu(menu* s,char name[],int num);
 * 5. 책이 위치한 곳을 알려주기(menu* s, char name[],int num);
 * 6. 책 대여하기 rent_menu(menu* s, char name[],int num);
 * 7. 책의 대여 가능 여부를 알려주기 is_rent_menu(menu* s,char name[],int num);
 * */

/*
우리가 만들어야 할 함수
+ 시작할때 txt파일에서
1) 메뉴 목록 불러오기
2) 전날 매출 가져오기

1. 신메뉴 추가
2. 메뉴 삭제
3. 메뉴 검색
4. 메뉴판 보기
5. 주문 추가
6. 주문 리스트 나열
7. 주문 취소
8. 총 매출 계산기

+ 끝날때
1) 메뉴목록 저장하기
2)오늘 매출 기록하기
*/

/*
메뉴 구조체 목록
1. 메뉴등록번호
2. 메뉴명
3. 가격 price
4. 종류 (커피, 스무디, ..)
*/

/*
주문 구조체 목록
1. 주문등록번호
2. 메뉴등록번호(뭘시켰는지) -> 가격을 알아내기 위해
3. 수량
4. 총금액
*/

typedef struct { // 메뉴 구조체 목록
  int no;        // 메뉴 등록 번호
  char name[50]; // 메뉴명
  int price;     // 가격
  int type;      // 종류

} menu;

typedef struct {
  int no;        // 메뉴 등록 번호
  int orno;      // 주문 등록 번호
  int menuconut; // 수량
  int total;     // 총금액
} order;

int selectMenu() {
  int menu;

  printf("\n***카페 매출 관리 프로그램***\n");
  printf("1. 신메뉴 추가\n");
  printf("2. 메뉴 삭제\n");
  printf("3. 메뉴 검색\n");
  printf("4. 메뉴판 보기\n");
  printf("5. 주문 추가\n");
  printf("6. 주문 취소\n");
  printf("7. 주문 리스트 나열\n");
  printf("8. 총 매출 계산기\n");
  printf("9. 메뉴 수정\n");
  printf("0. 종료하기 \n");
  printf("***************\n");
  printf("메뉴를 선택하세요: \n");

  scanf("%d", &menu);
  printf("\n");

  return menu;
}

menu *add_menu(menu *s, int num);               // 1. 신메뉴 추가
void del_menu(menu *s[], char name[], int num); // 2. 메뉴 삭제
void search_menu(menu *s, int num);             // 3. 메뉴 검색
void print_menu(menu *s[], int num);            // 4. 메뉴판 보기
void update_menu(menu *s);                      // 9. 메뉴 수정

order *add_order(order *s[], int num); // 5. 주문 추가
void del_order(order *s[], int num);   // 6. 주문 취소
void print_order(order *s[], int num); // 7. 주문 리스트 나열
void print_totalsales(order *s[]);    // 8. 총매출 계산

int main() {
  int select; // selectMenu에서 입력받는 변수
  int num;
  int menuconut = 0;   // 메뉴등록번호
  int ordercount = 0; // 주문등록번호
  char name[50];       //
  menu *b[100];        // 메뉴 구조체 포인터 선언 -> 메뉴는 b
  order *o[100];       // 주문 구조체 포인터 선언 -> 주문은 o
  int update_num; // 뭘 고칠지 입력받을때 쓰는 용도

  while (1) {
    select = selectMenu();
    if (select == 0)
      break;

    else if (select == 1) { // 1. 신메뉴 추가
      b[menuconut] = add_menu(b[menuconut], menuconut);
      menuconut++;
    }

    else if (select == 2) { // 2. 메뉴 삭제
      print_menu(b, menuconut);
      printf("삭제할 메뉴의 번호를 입력하세요. ex) 목록중 세번째로 나오면 3 "
             "입력 : ");
      scanf("%d", &num);
      b[num - 1]->no = -1;
      free(b[num - 1]);
    }

    else if (select == 3) { // 3. 메뉴 검색
      print_menu(b, menuconut);
      printf("검색할 메뉴의 번호를 입력하세요. ex) 목록중 세번째로 나오면 3 "
             "입력 : ");
      scanf("%d", &num);
      search_menu(b[num - 1], menuconut);
    }

    else if (select == 4) { // 4. 메뉴판 보기
      print_menu(b, menuconut);
    }

    else if (select == 5) { // 5. 주문 추가
      add_order(o, ordercount);
    }

    else if (select == 6) { // 6. 주문 취소
      del_order(o, ordercount);
    }

    else if (select == 7) { // 7. 주문 리스트 나열
      print_order(o, ordercount);
    }

    else if (select == 8) { // 8. 총매출 계산
      print_totalsales(o);
    }
      
    else if (select == 9) { // 9. 메뉴 수정
      print_menu(b, menuconut);
      printf("고칠 번호를 입력하시오.");
      scanf("%d", &update_num);
      update_menu(b[update_num]);
    }
  }
  
  return 0;
}

menu *add_menu(menu *s, int num) {
  s = (menu *)malloc(sizeof(menu));
  s->no = num; // 메뉴등록번호 0번부터 시작!

  printf("메뉴 이름을 입력하세요. ");
  scanf("%s", s->name);

  printf("메뉴의 가격을 입력하세요.\n");
  scanf("%d", &s->price);

  printf("메뉴의 종류를 선택하세요.\n");
  printf("0.커피 1.스무디 2.티 3.디저트류 4.기타\n");
  scanf("%d", &s->type);

  printf("\n성공적으로 추가되었습니다!\n");
  return s;
}

void update_menu(menu *s) {

  printf("메뉴 이름을 입력하세요: ");
  scanf("%s", s->name);

  printf("메뉴의 가격을 입력하세요.\n");
  scanf("%d", &s->price);

  printf("메뉴의 종류를 선택하세요.\n");
  printf("0.커피 1.스무디 2.티 3.디저트류 4.기타\n");
  scanf("%d", &s->type);

  printf("\n성공적으로 수정되었습니다!\n");
}

void search_menu(menu *s, int num) {
  printf("%d\t%s\t%d\t", s->no, s->name, s->price);
  if (s->type == 0)
    printf("커피");
  else if (s->type == 1)
    printf("스무디");
  else if (s->type == 2)
    printf("티");
  else if (s->type == 3)
    printf("디저트");
  else
    printf("기타");
  printf("\n");
}

void print_menu(menu *s[], int num) {
  printf("----------메뉴------------\n");
  if (num == 0)
    printf("등록된 메뉴가 없습니다.\n");
  printf("|번호 메뉴이름 가격 종류|\n");
  for (int i = 0; i < num; i++) {
    if (s[i]->no == -1)
      continue;
    else {
      printf("|");
      printf("%d %s  %d  %d |\n", s[i]->no, s[i]->name, s[i]->price,
             s[i]->type);
    }
  }
}

order *add_order(order *s[], int num) { // 5. 주문 추가
}

void del_order(order *s[], int num) { // 6. 주문 취소
}

void print_order(order *s[], int num) { // 7. 주문 리스트 나열
}

void print_totalsales(order *s[]) { // 8. 총매출 계산
}




//이건 상관없는거임!!! 그래도 혹시나 남겨봄
void rent_menu(menu *s[], int num) {
  char serch[50];
  printf("대여or반납 하실 책의 이름을 입력하세요: ");
  scanf("%s", serch);

  for (int i = 0; i < num; i++) {
    if (s[i]->no = -1)
      continue;
    else {
      if (strcmp(s[i]->name, serch) == 0) {
        if (s[i]->isRent == true) {
          printf("대여자 이름을 입력하시오: ");
          scanf("%s", s[i]->rentName);

          s[i]->isRent = false;

          printf("%s를 성공적으로 대여처리 하였습니다.\n", serch);
        } else {
          s[i]->isRent = true;
          printf("%s를 성공적으로 반납처리 하였습니다.\n", serch);
        }
        return;
      }
    }
  }
  printf("%s와 일치하는 이름을 찾지 못했습니다.\n", serch);
  return;
}

void is_rent_menu(menu *s[], int num) {
  char serch[50];
  printf("대여상황을 확인하실 책의 이름을 입력하세요: ");
  scanf("%s", serch);
  for (int i = 0; i < num; i++) {
    if (s[i]->no = -1)
      continue;
    else {
      if (strcmp(s[i]->name, serch) == 0) {
        if (s[i]->isRent == true) {
          printf("%s는 현재대여가 가능합니다.\n", serch);
        } else {
          printf("%s는 현재대여가 불가능 합니다.\n", serch);
          printf("대여자의 성함은 %s입니다. \n", s[i]->rentName);
        }
        return;
      }
    }
  }
  printf("%s와 일치하는 이름을 찾지 못했습니다.\n", serch);
  return;
}
