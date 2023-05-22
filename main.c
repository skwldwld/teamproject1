#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  int price;     //시킨 메뉴 하나의 가격
  int ordercon; // 수량
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
  printf("메뉴를 선택하세요: ");

  scanf("%d", &menu);
  printf("\n");

  return menu;
}

menu *add_menu(menu *s, int num); // 1. 신메뉴 추가
void del_menu(menu *s[], char name[], int num); // 2. 메뉴 삭제
void search_menu(menu *s, int num); // 3. 메뉴 검색
void print_menu(menu *s[], int num); // 4. 메뉴판 보기
void update_menu(menu *s); // 9. 메뉴 수정

order *add_order(order *s, int num); // 5. 주문 추가
int del_order(order *s[], int num); // 6. 주문 취소
void print_order(order *s[], int num); // 7. 주문 리스트 나열
void print_totalsales(int sum); // 8. 총매출 계산

int main() {
  int select; // selectMenu에서 입력받는 변수
  int num;
  int menucount = 0; // 메뉴등록번호
  int ordercount = 0; // 주문등록번호
  char name[50]; //
  menu *b[100]; // 메뉴 구조체 포인터 선언 -> 메뉴는 b
  order *o[100]; // 주문 구조체 포인터 선언 -> 주문은 o
  int update_num; // 뭘 고칠지 입력받을때 쓰는 용도
  int sum = 0 ;// 이게 총매출

  while (1) {
    select = selectMenu();
    if (select == 0)
      break;

    else if (select == 1) { // 1. 신메뉴 추가
      b[menucount] = add_menu(b[menucount], menucount);
      menucount++;
    }

    else if (select == 2) { // 2. 메뉴 삭제
      print_menu(b, menucount);
      printf("삭제할 메뉴의 번호를 입력하세요. (등록번호 입력)\n"
             "입력 : ");
      
      scanf("%d", &num);
      b[num]->no = -1;
    }

    else if (select == 3) { // 3. 메뉴 검색
      print_menu(b, menucount);
      printf("검색할 메뉴의 번호를 입력하세요. ex) 목록중 세번째로 나오면 3 입력\n"
             "입력 : ");
      scanf("%d", &num);
      search_menu(b[num - 1], menucount);
    }

    else if (select == 4) { // 4. 메뉴판 보기
      print_menu(b, menucount);
    }

    else if (select == 5) { // 5. 주문 추가
      print_menu(b, menucount);
      o[ordercount] = add_order(o[ordercount], ordercount);
      
      o[ordercount]->price=b[o[ordercount]->no]->price;
      o[ordercount]->total=o[ordercount]->price*o[ordercount]->ordercon;
      sum += o[ordercount]->total;
      ordercount++;
    }

    else if (select == 6) { // 6. 주문 취소
      print_menu(b, menucount);

      printf("\n");

      sum -= del_order(o, ordercount);
    }

    else if (select == 7) { // 7. 주문 리스트 나열
      printf("지금까지 주문한 목록은 다음과 같습니다.\n");
      print_order(o, ordercount);
    }

    else if (select == 8) { // 8. 총매출 계산
      print_totalsales(sum);
    }
      
    else if (select == 9) { // 9. 메뉴 수정
      print_menu(b, menucount);
      printf("고칠 번호를 입력하시오.");
      scanf("%d", &update_num);
      update_menu(b[update_num]);
    }
  }
  
  return 0;
}

menu *add_menu(menu *s, int num) { // 1. 메뉴 추가
  s = (menu *)malloc(sizeof(menu));
  s->no = num; // 메뉴등록번호 0번부터 시작!

  printf("메뉴 이름을 입력하세요.\n>> ");
  scanf("%s", s->name);

  printf("메뉴의 가격을 입력하세요.\n>> ");
  scanf("%d", &s->price);

  printf("메뉴의 종류를 선택하세요.\n");
  printf("0.커피 1.스무디 2.티 3.디저트류 4.기타\n>> ");
  scanf("%d", &s->type);

  printf("\n성공적으로 추가되었습니다!\n");
  
  return s;
}

void update_menu(menu *s) { // 9. 메뉴 수정

  printf("메뉴 이름을 입력하세요.\n>> ");
  scanf("%s", s->name);

  printf("메뉴의 가격을 입력하세요.\n>> ");
  scanf("%d", &s->price);

  printf("메뉴의 종류를 선택하세요.\n");
  printf("0.커피 1.스무디 2.티 3.디저트류 4.기타\n>> ");
  scanf("%d", &s->type);

  printf("\n성공적으로 수정되었습니다!\n");
}

void search_menu(menu *s, int num) { // 3. 메뉴 검색
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

void print_menu(menu *s[], int num) { // 4. 메뉴판 보기
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

/*
typedef struct {
  int no;        // 메뉴 등록 번호
  int price; //메뉴 하나의 가격
  int orno;      // 주문 등록 번호
  int ordercon; // 수량
  int total;     // 총금액
} order;
*/

order *add_order(order *o, int num) { // 5. 주문 추가
  o=(order*) malloc(sizeof(order));
  
  o->orno=num;
  printf("주문할 메뉴의 번호를 입력하세요. ");
  scanf("%d",&o->no);
  printf("주문할 수량을 입력하세요. ");
  scanf("%d",&o->ordercon);
  return o;
}

int del_order(order *s[], int num) { // 6. 주문 취소
  print_order(s, num);
  printf("취소할 주문 번호를 입력하세요. ");
  scanf("%d", &num);
  s[num]->no = -1;
  return s[num]->total;
}

void print_order(order *s[], int num) { // 7. 주문 리스트 나열
  int no;        // 메뉴 등록 번호
  int orno;      // 주문 등록 번호
  int menucount; // 수량
  int total;     // 총금액
  
  printf("---------주문내역-----------\n");
  if (num == 0)
    printf("주문내역이 없습니다.\n");
  printf("|주문번호 메뉴번호 수량 총금액|\n");
  for (int i = 0; i < num; i++) {
    if (s[i]->no == -1)
      continue;
    else {
      printf("|");
      printf("%d %d %d  %d |\n", s[i]->orno, s[i]->no, s[i]->ordercon,
             s[i]->total);
    }
  }
}

void print_totalsales(int sum) { // 8. 총매출 계산
  printf("오늘 하루 매출은 %d 원입니다.\n", sum);
}

void savefile(menu* s[],int num){//파일에 정보 저장하기
    FILE *fp = fopen("menu.txt","w");
    for(int i=0;i<num;i++){
      if(s[i]->no==-1) continue;
      else
        fprintf(fp,"%d %s %c %d\n",s[i]->no,s[i]->name,s[i]->type,s[i]->price);
    }
    fclose(fp);
    printf("파일에 정보가 저장됨!\n");
    return;
}
