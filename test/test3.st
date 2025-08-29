(*设置手动、半自动，自动三个大条件*)
(*手动：所有设备人工开关，仅显示到达的步骤*)

(*自动/半自动状态下，所有开关阀阀门投入自动，具备执行顺讯控制条件。下设启动、暂停、继续，停止按钮*)

(*自动状态下，点击暂停按钮，开关阀阀门不自动切换为手动，需操作人员人为切换为手动，动作保持，时间暂停*)

(*自动状态下，暂停后 点击继续按钮，操作人员手动操作阀门切为自动和原来阀位，若所有开关阀阀门没有打暂停
前阀位点击继续按钮，提示“阀位不正确”*)

(*半自动情况下，启动后，需点击下一步才能自动1至13步走完，停止，需再次点击下一步才进行14至15步，
走完15步后需点下一步才继续走到第1步*)

(*手动状态下，所有阀门具备面板手自动选择的权限，人工选择手自动*)

(*若自动，半自动下，人为点击阀门面板上自动切手动下，程序暂停*)

(*自动状态下，启动按钮,所有动作开始顺序执行*)

(*自动/半自动状态下，点击停止按钮,参数初始化（时间清零），阀位保持到停止时状态*)
(*自动/半自动状态下，根据程序切换模式：A运行/B再生，A运行/B运行，A再生/B运行，*)

(*测试按钮,工程师权限以上，检修期间，每点一次，走一步，动作对应步骤的输出结果*)
(*取消紧急停关闭所有阀门功能*)

RMP_SV:=PID_SV; (*位置调整*)

IF SWAM THEN	
	ST_:=ST;	
ELSE 
	ST_:=OFF;
	STEP:=0;
END_IF;

IF ST THEN	

	IF STEP=0 THEN 
		IF SW_S THEN 
			RMP_S:=S_SV;
			RMP_T:=ABS_ST(IN-PID_SV)/RMP_S;
			STEP:=1;
			TIMERS[NS1]:=0;	
		END_IF;	
	
		IF SW_T THEN 
			RMP_T:=T_SV;
			RMP_S:=ABS_ST(IN-PID_SV)/RMP_T;
			STEP:=1;
			TIMERS[NS1]:=0;	
		END_IF;		
	END_IF;	
		
	IF STEP=1 THEN 
		RMP_T:=RMP_T;
		RMP_S:=RMP_S(**60.0*);(*调整测试*)

		IF ABS_ST(IN-PID_SV) > (RMP_S(*/60.0*)) THEN
			IF IN > RMP_SV THEN		
				RMP_SV:=RMP_SV+(RMP_S(*/60.0*));
				STEP:=2;
				TIME:=(RMP_T+1.0-UINT_TO_REAL(TEMP1))/60.0; 
			END_IF; 
		
			IF IN < RMP_SV THEN		
				RMP_SV:=RMP_SV-(RMP_S(*/60.0*));
				STEP:=2;
				TIME:=(RMP_T+1.0-UINT_TO_REAL(TEMP1))/60.0; 
			END_IF; 
		ELSE
			RMP_SV:=IN;
			TIME:=0.0;
			ST_:=OFF;	
		END_IF;	
	END_IF;	

	IF STEP=2 THEN 
		IF TIMERS[NS1] >= TEMP1 THEN 
			TEMP1:=TEMP1+1;	
			STEP:=1;
		END_IF;		
	END_IF;

ELSE  
	STEP:=0;(*20211226取消屏蔽*)
	TEMP1:=2;
	TIME:=0.0;
END_IF;








	