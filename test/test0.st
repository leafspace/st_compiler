/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	test.st
*	作    者：	zhanglifei
*	创建日期：	2022/08/19
*	摘    要：	ST检查测试用例
*
***************************************************************************/

// 标识符
// ==============================================

// 标识符的第一个字符必须是字母或者下划线，最后一个字符必须是字母或数字，中间字符只允许是字母、数字或下划线。
IDENTIFIER := 0;                                           // [正确]
IDENTIFIER.IN := 0;                                        // [正确]
IDENTIFIER. := 0;                                          // [错误]
.IN := 0;                                                  // [错误]
_IDENTIFIER := 0;                                          // [正确]
IDENTIFIER1 := 0;                                          // [正确]
IDENTI_FIER := 0;                                          // [正确]
1IDENTIFIER := 0;                                          // [错误]
IDENT@IFIER := 0;                                          // [错误]

// 标识符中不允许连续出现两个连续的下划线。
1IDEN__TIFIER := 0;                                        // [错误]

// ==============================================

// 关键字
// ==============================================

// 关键字:TRUE、FALSE、ON、OFF
BOOL_IDENTIFIER := TRUE;                                   // [正确]
BOOL_IDENTIFIER := FALSE;                                  // [正确]
BOOL_IDENTIFIER := ON;                                     // [正确]
BOOL_IDENTIFIER := OFF;                                    // [正确]

// 关键字:IF THEN ELSIF ELSE END_IF
IF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSIF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSIF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSE
	IDENTIFIER := 0;
END_IF;                                                    // [正确]

IF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSIF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSE
	IDENTIFIER := 0;
END_IF;                                                    // [正确]

IF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
ELSE
	IDENTIFIER := 0;
END_IF;                                                    // [正确]

IF BOOL_IDENTIFIER THEN
	IDENTIFIER := 0;
END_IF;                                                    // [正确]

// 关键字:CASE OF ELSE END_CASE
CASE INT_IDENTIFIER OF
1:
	IDENTIFIER := 0;
2:
	IDENTIFIER := 0;
ELSE
	IDENTIFIER := 0;
END_CASE;                                                  // [正确]

CASE INT_IDENTIFIER OF
1:
	IDENTIFIER := 0;
2:
	IDENTIFIER := 0;
END_CASE;                                                  // [正确]

CASE INT_IDENTIFIER OF
1:
	IDENTIFIER := 0;
2.0:
	IDENTIFIER := 0;
END_CASE;                                                  // [正确]

CASE INT_IDENTIFIER OF
1:
	IDENTIFIER := 0;
2.1:
	IDENTIFIER := 0;
END_CASE;                                                  // [语义错误]

CASE INT_IDENTIFIER OF
1:
	IDENTIFIER := 0;
1:
	IDENTIFIER := 0;
END_CASE;                                                  // [语义错误]

// 关键字:FOR TO BY DO END_FOR
FOR IDENTIFIER := 1 TO 100 BY 1 DO
	IDENTIFIER := 0;
END_FOR;                                                   // [正确]

// 关键字:REPEAT UNTIL END_REPEAT
REPEAT
	IDENTIFIER := 0;
UNTIL BOOL_IDENTIFIER
END_REPEAT;                                                // [正确]


// 关键字:WHILE DO END_WHILE
WHILE BOOL_IDENTIFIER DO
	IDENTIFIER := 0;
END_WHILE;                                                 // [正确]

// 关键字:NOT,AND,OR,XOR
BOOL_IDENTIFIER := NOT BOOL_IDENTIFIER;                    // [正确]
BOOL_IDENTIFIER := NOT (BOOL_IDENTIFIER AND BOOL_IDENTIFIER); // [正确]
BOOL_IDENTIFIER := BOOL_IDENTIFIER AND BOOL_IDENTIFIER;    // [正确]
BOOL_IDENTIFIER := BOOL_IDENTIFIER OR BOOL_IDENTIFIER;     // [正确]
BOOL_IDENTIFIER := BOOL_IDENTIFIER XOR BOOL_IDENTIFIER;    // [正确]

// 关键字:MOD

INT_IDENTIFIER := INT_IDENTIFIER MOD INT_IDENTIFIER;       // [正确]

// 关键字:EXIT
WHILE BOOL_IDENTIFIER DO
	IDENTIFIER := 0;
	EXIT;
END_WHILE;                                                 // [正确]

IF BOOL_IDENTIFIER THEN
	EXIT;
END_IF;                                                    // [错误]

// ==============================================


// 分界符
// ==============================================

// 分界符:（**）、//、/**/
(*abcdefg*)                                                // [正确]
(*(*abcdefg*)*)                                            // [错误]
/*abcdefg*/                                                // [正确]


// 分界符:+
INT_IDENTIFIER := INT_IDENTIFIER + INT_IDENTIFIER;         // [正确]
INT_IDENTIFIER := +INT_IDENTIFIER;                         // [正确]

// 分界符:-
INT_IDENTIFIER := INT_IDENTIFIER - INT_IDENTIFIER;         // [正确]
INT_IDENTIFIER := -INT_IDENTIFIER;                         // [正确]

// 分界符:#
INT_IDENTIFIER := sINT#213;                                // [正确]
INT_IDENTIFIER := INT#123;                                 // [正确]
INT_IDENTIFIER := INT#-123;                                // [正确]
INT_IDENTIFIER := INT#+123;                                // [正确]
INT_IDENTIFIER := DINT#213;                                // [正确]
INT_IDENTIFIER := USINT#0123;                              // [正确]
INT_IDENTIFIER := UINT#123;                                // [正确]
INT_IDENTIFIER := UDINT#123;                               // [正确]
INT_IDENTIFIER := REAL#0.123;                              // [正确]
BOOL_IDENTIFIER := BOOL#0;                                 // [正确]
BOOL_IDENTIFIER := BOOL#1;                                 // [正确]
INT_IDENTIFIER := BOOL#213;                                // [错误]
INT_IDENTIFIER := 16#FFff;                                 // [正确]
INT_IDENTIFIER := 16#FFFF_FFFF;                            // [正确]
INT_IDENTIFIER := 8#7777_0001;                             // [正确]
INT_IDENTIFIER := 8#7877_0001;                             // [错误]
INT_IDENTIFIER := 8#7F77_0001;                             // [错误]
INT_IDENTIFIER := 16#FFFF_FFFZ;                            // [错误]

// 分界符:.
REAL_IDENTIFIER := 1.0;                                    // [正确]

// 分界符::=
IDENTIFIER := 1;                                           // [正确]

// 分界符:（）
INT_IDENTIFIER := (INT_IDENTIFIER + INT_IDENTIFIER);       // [正确]

// 分界符:；
IDENTIFIER := 1;                                           // [正确]

// 分界符:~
BOOL_IDENTIFIER := ~BOOL_IDENTIFIER;                       // [正确]

// 分界符:>
BOOL_IDENTIFIER := INT_IDENTIFIER > INT_IDENTIFIER;        // [正确]

// 分界符:>=
BOOL_IDENTIFIER := INT_IDENTIFIER >= INT_IDENTIFIER;       // [正确]

// 分界符:<
BOOL_IDENTIFIER := INT_IDENTIFIER < INT_IDENTIFIER;        // [正确]

// 分界符:<=
BOOL_IDENTIFIER := INT_IDENTIFIER <= INT_IDENTIFIER;       // [正确]

// 分界符:<>
BOOL_IDENTIFIER := INT_IDENTIFIER <> INT_IDENTIFIER;       // [正确]

// 分界符:=
BOOL_IDENTIFIER := INT_IDENTIFIER = INT_IDENTIFIER;        // [正确]

// 分界符:&
BOOL_IDENTIFIER := INT_IDENTIFIER & INT_IDENTIFIER;        // [错误]

// 分界符:|
BOOL_IDENTIFIER := INT_IDENTIFIER | INT_IDENTIFIER;        // [错误]

// ==============================================

// 语法规则
// ==============================================

// 定时器
TIMERS(100);                                               // [正确]

TIMERS(100, 100);                                          // [语义错误]

TIMERS(true);                                              // [语义错误]

// ==============================================

// 语义错误
// ==============================================
ABCFUNC(100);                                              // [语义错误]

CONST_IDENTIFIER := 100;                                   // [语义错误]

4;                                                         // [语义错误]

100 > 200;                                                 // [语义错误]

(100 + 200);                                               // [语义错误]

// ==============================================