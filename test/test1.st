/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	test.st
*	作    者：	zhanglifei
*	创建日期：	2022/08/19
*	摘    要：	ST检查测试用例 （类型相关错误）
*
***************************************************************************/

// 二元操作符相关

INT_IDENTIFIER := 100 MOD 50;                              // [正确]
INT_IDENTIFIER := 100 MOD FALSE;                           // [语义错误]
BOOL_IDENTIFIER := NOT BOOL_IDENTIFIER;                    // [正确]
BOOL_IDENTIFIER := NOT 100;                                // [语义错误]

INT_IDENTIFIER := 100 + 100;                               // [正确]
INT_IDENTIFIER := 100 - 100;                               // [正确]
INT_IDENTIFIER := 100 * 100;                               // [正确]
INT_IDENTIFIER := 100 / 100;                               // [正确]

INT_IDENTIFIER := 100 + FALSE;                             // [语义错误]
INT_IDENTIFIER := 100 - FALSE;                             // [语义错误]
INT_IDENTIFIER := 100 * FALSE;                             // [语义错误]
INT_IDENTIFIER := 100 / FALSE;                             // [语义错误]

INT_IDENTIFIER := 100 ** 100;                              // [正确]
INT_IDENTIFIER := 100 ** FALSE;                            // [语义错误]

BOOL_IDENTIFIER := (true OR 100);                          // [语义错误]
BOOL_IDENTIFIER := (true XOR 100);                         // [语义错误]
BOOL_IDENTIFIER := (true AND 100);                         // [语义错误]
BOOL_IDENTIFIER := (true = 100);                           // [语义错误]
BOOL_IDENTIFIER := (true <> 100);                          // [语义错误]
BOOL_IDENTIFIER := (true > 100);                           // [语义错误]
BOOL_IDENTIFIER := (true >= 100);                          // [语义错误]
BOOL_IDENTIFIER := (true < 100);                           // [语义错误]
BOOL_IDENTIFIER := (true <= 100);                          // [语义错误]

BOOL_IDENTIFIER := 100;                                    // [语义错误]

IF (FALSE, TRUE)                                           // [语义错误]
;

IF (100)                                                   // [语义错误]
;

CASE INT_IDENTIFIER OF
1.1:
	IDENTIFIER := 0;
FALSE:
	IDENTIFIER := 0;
END_CASE;                                                  // [语义错误]

FOR IDENTIFIER := 1 TO 100 BY 1 DO
	IDENTIFIER := 0;
END_FOR;                                                   // [正确]

FOR IDENTIFIER := 1 TO FALSE BY 1 DO
	IDENTIFIER := 0;
END_FOR;                                                   // [语义错误]

WHILE FALSE DO
	IDENTIFIER := 0;
END_WHILE;                                                 // [正确]

WHILE 100 DO
	IDENTIFIER := 0;
END_WHILE;                                                 // [语义错误]

REPEAT
	IDENTIFIER := 0;
UNTIL BOOL_IDENTIFIER
END_REPEAT;                                                // [正确]

REPEAT
	IDENTIFIER := 0;
UNTIL 100
END_REPEAT;                                                // [语义错误]