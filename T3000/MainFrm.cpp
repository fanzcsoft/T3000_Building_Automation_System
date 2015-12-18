
// MainFrm.cpp : implementation of the CMainFrame class
//DoConnectToANode

#include "stdafx.h"
#include "T3000.h"
#include "Scanwaydlg.h"
#include "MainFrm.h"
#include "T3000Doc.h"
#include "T3000TableView.h"
#include "T3000view.h"
#include "WorkspaceBar.h"
#include "NetworkControllView.h"
#include "T3000DefaultView.h"
#include "global_variable_extern.h"
#include "globle_function.h"
#include "AddBuilding.h"
#include "ScanSelectDlg.h"

#include "MannageBuidingDlg.h"
#include "AllNodesDiaolg.h"
#include "GridLoad.h"
#include "GridFlashDlg.h"
#include "ScanDbWaitDlg.h"
#include "ChangePasswordDlg.h"
#include "ManageAccountDlg.h"
#include "LoginDlg.h"
#include "AfxMessageDialog.h"
#include "ImportDatabaseDlg.h"

#include "EreaseDlg.h"

#include "hangeIDDlg.h"
#include "LightingController/LightingController.h"//Lightingcontroller
#include "NewHumChamberView.h"
#include "CO2_View.h"
//#include "MbpGlobals.h"
#include "Dialog_Progess.h"

#include "excel9.h"
#include "ScanSelectDlg.h"

#include "BacnetTool.h"
#include "BacnetAlarmWindow.h"
#include "Dialog_Progess.h"
#include "TStatOutputView.h"
extern CDialog_Progess *WaitRead_Data_Dlg;
//////////////////////////////
//#include "isp/CDialogISPTOOL.h"

#include "IONameConfig.h"

#include "DialogCM5_BacNet.h"

#include "T38I13O.h"
#include "T332AI.h"
#include "gloab_define.h"

#include "BacnetUserlogin.h"
#include "BacnetAddLabel.h"
extern CBacnetAddLabel * Add_Label_Window;
extern CBacnetUserlogin * User_Login_Window;
#include "T38AI8AO.h"
#include "rs485.h" // For call Get_RS485_Handle() function
#include "BacnetWait.h"
#include "BacnetScreenEdit.h"
#include "LanguageLocale.h"
#include "RegisterViewerDlg.h"
#include "DebugWindow.h"
#include "PVDlg.h"
#include "T36CT.h"
#include "T3RTDView.h"
#include "CO2NetView.h"
#include "htmlhelp.h"
#include "T3000UpdateDlg.h"
#include "Dowmloadfile.h"
#include "ptp.h"
#include "datalink.h"
#include "TCP_Server.h"
#include "PressureSensorForm.h"
#include "TroubleShootDlg.h"
#include "TempHumSensorForm.h"
#include "bado/BADO.h"

#include <algorithm>
#include "BacnetMonitor.h"
#include "T3ModulesView.h"
#include "T3000_Default_MainView.h"
#include "T3ModulesOutputDlg.h"
#include "ProductRegisterListView.h"
#include "TStatInputView.h"

#include "BoatMonitorViewer.h"

bool b_create_status = false;
const TCHAR c_strCfgFileName[] = _T("config.txt");
//	配置文件名称，用于保存用户设置
extern bool b_statusbarthreadflag;
extern tree_product	m_product_isp_auto_flash;
#pragma region Fance Test
//For Test
// 在没有鼠标和键盘消息的时候 就启用自动刷新 treeview,如果有就 不要刷新，因为如果正在刷新，客户肯能就无法第一时间读到自己想要的数据;

bool start_record_time = true;	//开启计时，如果用户一段时间无键盘和鼠标左键操作就开启自动刷新;
unsigned long time_click = 0;

bool enable_show_debug_window = false;
BacnetWait *WaitWriteDlg=NULL;
HANDLE hwait_write_thread = NULL;
_Refresh_Write_Info Write_Config_Info;
HANDLE hStartEvent; // thread start event
extern int isp_product_id;
vector <MSG> My_Receive_msg;
#define WM_CREATE_STATUSBAR WM_USER + 638
#define  WM_REFRESH_TREEVIEW_MAP WM_USER + 2008
HANDLE hDeal_thread;
DWORD nThreadID_Do;
extern CBacnetScreenEdit * ScreenEdit_Window;
extern CBacnetAlarmWindow * AlarmWindow_Window;
extern bool m_is_remote_device ;

#include "BacnetScreen.h"
#include "BacnetProgram.h"
#include "BacnetInput.h"
#include "BacnetOutput.h"
#include "BacnetVariable.h"
#include "BacnetAnnualRoutine.h"
#include "BacnetWeeklyRoutine.h"
#include "BacnetController.h"
#include "BacnetMonitor.h"
#include "BacnetAlarmLog.h"
#include "BacnetTstat.h"
#include "BacnetRemotePoint.h"
extern BacnetScreen *Screen_Window;
extern CBacnetProgram *Program_Window;
extern CBacnetInput *Input_Window ;
extern CBacnetOutput *Output_Window ;
extern CBacnetVariable *Variable_Window ;
extern BacnetWeeklyRoutine *WeeklyRoutine_Window ;
extern BacnetAnnualRoutine *AnnualRoutine_Window ;
extern BacnetController *Controller_Window ;
extern CBacnetMonitor *Monitor_Window ;
extern CBacnetAlarmLog *AlarmLog_Window ;
extern CBacnetTstat *Tstat_Window ;
extern CBacnetRemotePoint* Remote_Point_Window ;
extern int bacnet_view_number;

CCriticalSection MyCriticalSection;

bool b_pause_refresh_tree = false;
char local_network_ip[255];
CString local_enthernet_ip;
int m_MainHotKeyID[14] =
{
    3001,
    3002,
    3003,
    3004,
    3005,
    3006,
    3007,
    3008,
    3009,
    3010,
    3011,
    3012,
    3013
};

//End for Test
void CALLBACK Listen(SOCKET s, int ServerPort, const char *ClientIP);
#pragma endregion
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

// #define _CRTDBG_MAP_ALLOC
// #include "stdlib.h"
// #include "crtdbg.h"
#include "T3000RegAddress.h"
T3000RegAddress MyRegAddress;

#include "ScanDlg.h"
#pragma comment(lib, "Version.lib")

// #include "productDB/ProInterface.h"
// #pragma comment(lib,"productDB/ProductDBdll.lib")


#ifdef _DEBUG
    #define new DEBUG_NEW


#endif
// CMainFrame
#define REFRESH_TIMER	1
#define REFRESH_TIMER_VALUE	 35000
#define ID_NODEFAULTMAINBUILDING_MSG 8000
#define SCAN_TIMER 2
#define MONITOR_MOUSE_KEYBOARD_TIMER 3
#define SAVE_PRODYCT_STATUS  4

#define MESSAGE_INFORMATION_DEAL 5

const UINT WM_HTTPDOWNLOAD_THREAD_FINISHED = WM_APP + 100;
CEvent g_killMultiReadEvent;

volatile HANDLE Read_Mutex=NULL;
//CEvent g_pauseMultiReadEvent;
extern CT3000TableView* pTableView;
//BOOL g_bPauseMultiRead=FALSE;
BOOL m_active_key_mouse = FALSE;
//tree0412
#if 0//原有
    #define TVINSERV_BUILDING 		{tvInsert.item.iImage=0;tvInsert.item.iSelectedImage=0;}
    #define TVINSERV_FLOOR	 			{tvInsert.item.iImage=0;tvInsert.item.iSelectedImage=0;}
    #define TVINSERV_ROOM				{tvInsert.item.iImage=1;tvInsert.item.iSelectedImage=1;}
    #define TVINSERV_TSTAT 			{tvInsert.item.iImage=2;tvInsert.item.iSelectedImage=2;}
    #define TVINSERV_LED 				{tvInsert.item.iImage=3;tvInsert.item.iSelectedImage=3;}
    #define TVINSERV_NET_WORK		{tvInsert.item.iImage=5;tvInsert.item.iSelectedImage=5;}
    #define TVINSERV_SOLAR				{tvInsert.item.iImage=5;tvInsert.item.iSelectedImage=5;}
    #define TVINSERV_CMFIVE			{tvInsert.item.iImage=4;tvInsert.item.iSelectedImage=4;} //CM5
    #define TVINSERV_MINIPANEL		{tvInsert.item.iImage=7;tvInsert.item.iSelectedImage=7;} //MiniPanel
#endif

//tree0412
#if 1
    #define TVINSERV_BUILDING 		    {tvInsert.item.iImage=0; tvInsert.item.iSelectedImage=0;}
    #define TVINSERV_FLOOR	 			{tvInsert.item.iImage=0; tvInsert.item.iSelectedImage=0;}
    #define TVINSERV_ROOM				{tvInsert.item.iImage=2; tvInsert.item.iSelectedImage=2;}
    #define TVINSERV_TSTAT 			    {tvInsert.item.iImage=6; tvInsert.item.iSelectedImage=6;}
    #define TVINSERV_LED 				{tvInsert.item.iImage=8; tvInsert.item.iSelectedImage=8;}//TSTAT6&7
    #define TVINSERV_NET_WORK		    {tvInsert.item.iImage=12;tvInsert.item.iSelectedImage=12;}
    #define TVINSERV_SOLAR				{tvInsert.item.iImage=12;tvInsert.item.iSelectedImage=12;}
    #define TVINSERV_CMFIVE			    {tvInsert.item.iImage=10;tvInsert.item.iSelectedImage=10;} //CM5
    #define TVINSERV_MINIPANEL		    {tvInsert.item.iImage=14;tvInsert.item.iSelectedImage=14;} //MiniPanel
    #define TVINSERV_LC				    {tvInsert.item.iImage=16;tvInsert.item.iSelectedImage=16;} //Lightingcontroller
    #define TVINSERV_TSTAT6			    {tvInsert.item.iImage=18;tvInsert.item.iSelectedImage=18;}//tstat6
    #define TVINSERV_CO2			    {tvInsert.item.iImage=20;tvInsert.item.iSelectedImage=20;}//CO2
    #define TVINSERV_CS3000             {tvInsert.item.iImage=22;tvInsert.item.iSelectedImage=22;}//cs3000
#endif

#define ITEM_MASK				TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
    ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
    ON_MESSAGE(WM_REFRESH_TREEVIEW_MAP, RefreshTreeViewMap)
    ON_MESSAGE(WM_SCAN_PRODUCT, Message_Scan_Product)
    ON_MESSAGE(MY_BAC_CONFIG_READ_RESULTS, ReadConfigFromDeviceMessageCallBack)
    ON_MESSAGE(MY_RESUME_DATA, AllWriteMessageCallBack)
    ON_MESSAGE(MY_RX_TX_COUNT, Refresh_RX_TX_Count)
    //ON_MESSAGE(WM_SHOW_PANNELINFOR,Show_Panel)
    ON_MESSAGE(WM_DELETE_NEW_MESSAGE_DLG,Delete_Write_New_Dlg)
    ON_MESSAGE(WM_HOTKEY,&CMainFrame::OnHotKey)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
    ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
    ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)

    //ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, //OnToolbarReset) // 工具栏的按钮添加文字的方法
    ON_COMMAND(ID_BUILDINGBAR,OnCheckBuildingBar)
    ON_UPDATE_COMMAND_UI(ID_BUILDINGBAR, OnUpdateCheckBuildingBar)
    ON_COMMAND(ID_INPUTOUTPUTPANE,OnCheckIOPane)
    ON_UPDATE_COMMAND_UI(ID_INPUTOUTPUTPANE, OnUpdateCheckIOPane)

    ON_COMMAND(ID_FILE_SAVE_CONFIG, OnFileOpen)
    ON_COMMAND(ID_CONFIGFILE_SAVE_AS, SaveConfigFile)
    ON_COMMAND(ID_LOAD_CONFIG,OnLoadConfigFile)

    //ON_COMMAND(ID_TOOL_SCAN,OnScanDevice)

    ON_COMMAND(ID_ALLNODESDATABASE,OnAllNodeDatabase)
    ON_COMMAND( ID_FILE_LOADCONFIGFILE,OnLoadConfigFile)
    ON_COMMAND(ID_FILE_BATCHBURNHEX,OnBatchFlashHex)
    ON_COMMAND(ID_FILE_IMPORTDATAFROMDATABASEFILE,OnImportDatase)

    ON_COMMAND(ID_RW_INFO, OnLabel)
    ON_COMMAND(ID_BUILDING_INFO, OnLabe2)
    ON_COMMAND(ID_PROTOCOL_INFO, OnLabe3)

    ON_MESSAGE(WM_CREATE_STATUSBAR,OnCreateStatusBarWindow)
    ON_MESSAGE(WM_USER_FRESHSTATUSBAR,OnFreshStatusBar)
    ON_MESSAGE(WM_ADDTREENODE, OnAddTreeNode)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_COMMAND(ID_USERACCOUNT_CHANGEPASSWORD,OnChangeAdminPassword)
    ON_COMMAND(ID_USERACCOUNT_MANNAGEUSER,OnUserMannageMent)
    ON_UPDATE_COMMAND_UI(ID_USERACCOUNT_MANNAGEUSER,OnUserMannageMentUpdate)
    ON_COMMAND(ID_USERACCOUNT_LOGIN,OnUserLogin)
    ON_COMMAND(ID_HELP,OnHelp)
    ON_COMMAND(ID_TOOL_EREASE_CHANGE_ID,OnToolErease)
    ON_COMMAND(ID_TOOL_FRESH,OnToolFresh)
    ON_COMMAND(ID_TOOL_FRESHLEFTTREEVIEW,OnToolRefreshLeftTreee)

    //ON_COMMAND(ID_DATABASE_TEMCOPRODUCTS, &CMainFrame::OnDatabaseTemcoproducts)
    //ON_COMMAND(ID_FILE_ISPTOOL, &CMainFrame::OnFileIsptool)
    /*ON_MESSAGE(WM_DLG_CLOSE, OnDlgClose)*/
    ON_COMMAND(ID_DATABASE_MBPOLL, &CMainFrame::OnDatabaseMbpoll)
    /*ON_MESSAGE(WM_MBPOLL_CLOSED, &CMainFrame::OnMbpollClosed)*/
    ON_COMMAND(ID_DATABASE_IONAMECONFIG, &CMainFrame::OnDatabaseIonameconfig)
    ON_COMMAND(ID_TOOL_ISPTOOLFORONE, &CMainFrame::OnToolIsptoolforone)

//	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
    ON_COMMAND(ID_VIEW_COMMUNICATETRAFFIC, &CMainFrame::OnViewCommunicatetraffic)

    ON_COMMAND(ID_CONTROL_MAIN, &CMainFrame::OnControlMain)
    ON_COMMAND(ID_CONTROL_INPUTS, &CMainFrame::OnControlInputs)
    ON_COMMAND(ID_CONTROL_PROGRAMS, &CMainFrame::OnControlPrograms)
    ON_COMMAND(ID_CONTROL_OUTPUTS, &CMainFrame::OnControlOutputs)
    ON_COMMAND(ID_CONTROL_VARIABLES, &CMainFrame::OnControlVariables)
    ON_COMMAND(ID_CONTROL_WEEKLY, &CMainFrame::OnControlWeekly)
    ON_COMMAND(ID_CONTROL_ANNUALROUTINES, &CMainFrame::OnControlAnnualroutines)
    ON_COMMAND(ID_MISCELLANEOUS_LOADDESCRIPTORS, &CMainFrame::OnMiscellaneousLoaddescriptors)
    ON_COMMAND(ID_MISCELLANEOUS_UPDATEMINI, &CMainFrame::OnMiscellaneousUpdatemini)
    ON_COMMAND(ID_CONTROL_CONTROLLERS, &CMainFrame::OnControlControllers)
    ON_COMMAND(ID_CONTROL_SCREENS, &CMainFrame::OnControlScreens)
    ON_COMMAND(ID_CONTROL_MONITORS, &CMainFrame::OnControlMonitors)
    ON_COMMAND(ID_HELP_GETLANGUAGECONFIGFILE, &CMainFrame::OnHelpGetlanguageconfigfile)
    ON_COMMAND(ID_LANGUAGE_ENGLISH, &CMainFrame::OnLanguageEnglish)
    ON_COMMAND(ID_LANGUAGE_34010, &CMainFrame::OnLanguage34010)
    ON_COMMAND(ID_LANGUAGE_34006, &CMainFrame::OnLanguage34006)
    ON_COMMAND(ID_TOOL_REGISTERVIEWER, &CMainFrame::OnToolRegisterviewer)
    ON_WM_SIZING()
    ON_WM_PAINT()
    ON_COMMAND(ID_DATABASE_BACNETTOOL, &CMainFrame::OnDatabaseBacnettool)
    ON_COMMAND(ID_CONTROL_ALARM_LOG, &CMainFrame::OnControlAlarmLog)
    ON_COMMAND(ID_Menu_CHECKUPDATE, &CMainFrame::OnMenuCheckupdate)
    ON_COMMAND(ID_DATABASE_PV, &CMainFrame::OnDatabasePv)
    ON_COMMAND(ID_CONTROL_TSTAT, &CMainFrame::OnControlTstat)


    ON_COMMAND(ID_CONNECT2,OnConnect)
    ON_UPDATE_COMMAND_UI(ID_CONNECT2, &CMainFrame::OnUpdateConnect2)
    ON_COMMAND(ID_DISCONNECT2,OnDisconnect)
    ON_UPDATE_COMMAND_UI(ID_DISCONNECT2, &CMainFrame::OnUpdateDisconnect2)
    ON_COMMAND(ID_SCAN,OnScanDevice)
    ON_UPDATE_COMMAND_UI(ID_SCAN, &CMainFrame::OnUpdateScanDevice)
    ON_COMMAND(ID_BUILDINGCONFIGDB,OnAddBuildingConfig)
    ON_UPDATE_COMMAND_UI(ID_BUILDINGCONFIGDB, &CMainFrame::OnUpdateAddBuildingConfig)

    ON_WM_COPYDATA()
    ON_COMMAND(ID_HELP_UPDATEFIRMWARE, &CMainFrame::OnHelpUpdatefirmware)


    ON_UPDATE_COMMAND_UI(IDS_SHOW_RESULTS, &CMainFrame::OnUpdateStatusBar)
    //ON_UPDATE_COMMAND_UI(ID_INDICATOR_FILEPOS, &CMainFrame::OnUpdatePaneFilePos)


    ON_COMMAND(ID_HELP_FEEDBACKTOTEMCO, &CMainFrame::OnHelpFeedbacktotemco)

    ON_COMMAND(ID_CONTROL_CUSTOMERUNITS, &CMainFrame::OnControlCustomerunits)
    ON_COMMAND(ID_MISCELLANEOUS_GSMCONNECTION, &CMainFrame::OnMiscellaneousGsmconnection)



    ON_MESSAGE(WM_HTTPDOWNLOAD_THREAD_FINISHED, OnThreadFinished)
    ON_COMMAND(ID_CONTROL_SETTINGS, &CMainFrame::OnControlSettings)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_MAIN, &CMainFrame::OnUpdateControlMain)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_INPUTS, &CMainFrame::OnUpdateControlInputs)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_OUTPUTS, &CMainFrame::OnUpdateControlOutputs)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_VARIABLES, &CMainFrame::OnUpdateControlVariables)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_PROGRAMS, &CMainFrame::OnUpdateControlPrograms)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_SCREENS, &CMainFrame::OnUpdateControlScreens)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_CONTROLLERS, &CMainFrame::OnUpdateControlControllers)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_WEEKLY, &CMainFrame::OnUpdateControlWeekly)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_ANNUALROUTINES, &CMainFrame::OnUpdateControlAnnualroutines)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_MONITORS, &CMainFrame::OnUpdateControlMonitors)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_ALARM_LOG, &CMainFrame::OnUpdateControlAlarmLog)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_TSTAT, &CMainFrame::OnUpdateControlTstat)
    ON_UPDATE_COMMAND_UI(ID_CONTROL_SETTINGS, &CMainFrame::OnUpdateControlSettings)
    ON_COMMAND(ID_TOOL_DETECTONLINEPRODUCTS, &CMainFrame::OnToolDetectonlineproducts)
    ON_WM_HELPINFO()
    ON_COMMAND(ID_FILE_EXPORTREGISETERSLIST, &CMainFrame::OnFileExportregiseterslist)
    //  ON_COMMAND(ID_TOOL_PRODUCTSREGISTERSMAINTENANCE, &CMainFrame::OnToolProductsregistersmaintenance)
    ON_COMMAND(ID_TOOL_REGISTERSMAINTENANCESYSTEM, &CMainFrame::OnToolRegistersmaintenancesystem)
    ON_COMMAND(ID_TOOL_FLASHSN, &CMainFrame::OnToolFlashsn)
    ON_WM_MOVE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
    //ID_SEPARATOR,           // status line indicator
    ID_RW_INFO,
    ID_BUILDING_INFO,
    ID_PROTOCOL_INFO,
    IDS_SHOW_RESULTS,

};

unsigned short tempchange[512];
int index_Count=0;
UINT _ReadMultiRegisters(LPVOID pParam)
{

    CMainFrame* pFrame=(CMainFrame*)(pParam);
    BOOL bFirst=TRUE;
    Read_Mutex=CreateMutex(NULL,TRUE,_T("Read_Multi_Reg"));
    ReleaseMutex(Read_Mutex);
    /*Sleep(30*1000);*/
    CString g_strT3000LogString;
    //forbid  _ReadMultiRegisters  and _FreshTreeView access com port at the same time.

    while(1)
    {
        if(::WaitForSingleObject(g_killMultiReadEvent,0)==WAIT_OBJECT_0)
            break;

        g_bEnableRefreshTreeView = TRUE;
        if (pFrame->m_lastinterface !=19)
        {
            bFirst = FALSE;
        }
        if(!bFirst)
        {
            Sleep(10000);

            g_bEnableRefreshTreeView = FALSE;

            if(g_bPauseMultiRead)
            {
                Sleep(10);
                continue;
            }
            if(g_tstat_id_changed)
            {
                Sleep(10);
                continue;
            }

            if(g_tstat_id<0||g_tstat_id>=255)
            {
                Sleep(10);
                continue;
            }

            //Make sure the view is TSTATE VIEW ,if not ,don't read this register.
            CView* pT3000View = pFrame->m_pViews[DLG_T3000_VIEW];
            if (!pT3000View)
            {
                Sleep(10);
                continue;
            }
            CView* pActiveView =pFrame->GetActiveView();
            if(pActiveView != pT3000View)
            {
                Sleep(10);
                continue;
            }
        }
        if (!is_connect())
        {
            Sleep(10);
            continue;
        }
        bFirst=FALSE;
        WaitForSingleObject(Read_Mutex,INFINITE);

        int nRet =read_one(g_tstat_id,6,2);

        if(nRet<0)
        {
            ReleaseMutex(Read_Mutex);//Add by Fance .
            continue;
        }

        for(int i=0; i<17; i++) //Modify by Fance , tstat 6 has more register than 512;
        {
            if(g_tstat_id_changed)
            {
                Sleep(10);
                continue;
            }
            if(g_bPauseMultiRead)
            {
                Sleep(10);
                continue;
            }
            //register_critical_section.Lock();
            //
            int multy_ret = 0;
            multy_ret = Read_Multi(g_tstat_id,&multi_register_value[i*100],i*100,100);
            //register_critical_section.Unlock();
            Sleep(100);
            if(multy_ret<0)		//Fance : 如果出现读失败 就跳出循环体,因为如果是由断开连接 造成的 读失败 会使其他需要用到读的地方一直无法获得资源;
                break;
        }

        ReleaseMutex(Read_Mutex);//Add by Fance .

        //Fance_1
        memcpy_s(product_register_value,sizeof(product_register_value),multi_register_value,sizeof(multi_register_value));


        CString achive_file_path;
        CString temp_serial;
        temp_serial.Format(_T("%u.prg"),g_selected_serialnumber);
        achive_file_path = g_achive_folder + _T("\\") + temp_serial;

        Save_Product_Value_Cache(achive_file_path);
        if(pFrame->m_pViews[DLG_T3000_VIEW]->m_hWnd!=NULL)
        {
            if (!m_active_key_mouse)
            {
                //::PostMessage(pFrame->m_pViews[DLG_T3000_VIEW]->m_hWnd,MsgT3000ViewFresh,0,0);
            }

        }



    }



    return 1;
}



UINT __cdecl  _FreshTreeView(LPVOID pParam );

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
    theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
    m_nStyle=0;
    m_strCurSubBuldingName.Empty();
    m_strCurMainBuildingName.Empty();
    m_nBaudrate=19200;
    m_pThreadScan=NULL;
    m_pFreshMultiRegisters=NULL;
    m_hCurCommunication=NULL;
    m_bScanFinished=FALSE;
    m_nCurSubBuildingIndex=-1;
    m_bScanALL=FALSE;
    m_strIP=_T("");
    list_mouse_click = false;
    //////////////////////////////////////////////////////////////////////////
    m_bEnableRefreshTreeView = TRUE;
    m_pRefreshThread = NULL;

    m_pWaitScanDlg = NULL;
    m_pScanner = NULL;
    FistWdb = TRUE;
    m_isCM5=FALSE;
    FlagSerialNumber = 0;
    m_frist_start=TRUE;
    m_bDialogOpen = FALSE;
    mbPollDlgOpen = FALSE;



    m_hInternetSession = NULL;
    m_hHttpConnection = NULL;
    m_hHttpFile = NULL;

    m_bSafeToClose = TRUE;
    m_pDialogInfo = NULL;


}


CMainFrame::~CMainFrame()
{
    if (m_pScanner != NULL)
    {
        delete m_pScanner;
        m_pScanner = NULL;
    }
    if (is_connect())
    {
        close_com(); // added by zgq:12-16-2011
    }


}
void CMainFrame::InitViews()
{
    m_nCurView = 0;
    CView* pActiveView = GetActiveView();
    if(pActiveView==NULL)
        return;
    m_pViews[DLG_T3000_VIEW] = pActiveView;
    m_pViews[DLG_NETWORKCONTROL_VIEW]=(CView*) new CNetworkControllView();
    m_pViews[DLG_GRAPGIC_VIEW]=(CView*) new CGraphicView();
    m_pViews[DLG_TRENDLOG_VIEW]=(CView*) new CTrendLogView();
    m_pViews[DLG_DIALOGCM5_VIEW]=  NULL; //(CView*) new CDialogCM5(); //CM5
    m_pViews[DLG_DIALOGT3_VIEW]=(CView*) new CDialogT3();  //T3
    //m_pViews[DLG_DIALOGMINIPANEL_VIEW]=(CView*) new CDialgMiniPanel();//Mini Panel
    m_pViews[DLG_AIRQUALITY_VIEW]=(CView*) new CAirQuality;//AirQuality
    m_pViews[DLG_LIGHTINGCONTROLLER_VIEW]=(CView*) new CLightingController;//Lightingcontroller
    m_pViews[DLG_HUMCHAMBER]=(CView*) new CNewHumChamberView;
    m_pViews[DLG_CO2_VIEW]=(CView*) new CCO2_View;
    m_pViews[DLG_CO2_NET_VIEW]=(CView*)new CCO2NetView;
    m_pViews[DLG_BACNET_VIEW]=(CView*) new CDialogCM5_BacNet; //CM5
    m_pViews[DLG_DIALOGT38I13O_VIEW]=(CView*) new T38I13O;
    m_pViews[DLG_DIALOGT332AI_VIEW]=(CView*)new T332AI;
    m_pViews[DLG_DIALOGT38AI8AO]=(CView*)new T38AI8AO;
    m_pViews[DLG_DIALOGT36CT]=(CView*)new T36CT;
    m_pViews[DLG_DIALOGT3PT10]=(CView*)new CT3RTDView;
    m_pViews[DLG_DIALOG_PRESSURE_SENSOR]=(CView*)new CPressureSensorForm;
    m_pViews[DLG_DIALOG_DEFAULT_BUILDING]=(CView*)new CT3000DefaultView;
    m_pViews[DLG_DIALOG_TEMP_HUMSENSOR]=(CView*)new CTempHumSensorForm;
    m_pViews[DLG_DIALOG_DEFAULT_T3000_VIEW] = (CView * )new T3000_Default_MainView;
    m_pViews[DLG_DIALOG_T3_INPUTS_VIEW] = (CView * )new CT3ModulesView;
    m_pViews[DLG_DIALOG_T3_OUTPUTS_VIEW] = (CView * )new CT3ModulesOutputDlg;
    m_pViews[DLG_DIALOG_CUSTOM_VIEW]  = (CView * )new CProductRegisterListView;
    m_pViews[DLG_DIALOG_TSTAT_INPUT_VIEW]=(CView *)new CTStatInputView;
    m_pViews[DLG_DIALOG_TSTAT_OUTPUT_VIEW]=(CView *)new CTStatOutputView;
    m_pViews[DLG_DIALOG_BOATMONITOR] = (CView *)new CBoatMonitorViewer;
    CDocument* pCurrentDoc = GetActiveDocument();
    CCreateContext newContext;
    newContext.m_pNewViewClass = NULL;
    newContext.m_pNewDocTemplate = NULL;
    newContext.m_pLastView = NULL;
    newContext.m_pCurrentFrame = NULL;
    newContext.m_pCurrentDoc = pCurrentDoc;

    CRect rect(0, 0, 0, 0);

    for (int nView =1; nView < NUMVIEWS; nView++)
    {
        if(nView == DLG_DIALOGCM5_VIEW||nView == DLG_DIALOGMINIPANEL_VIEW)
            continue;
        m_pViews[nView]->Create(NULL, NULL,
                                (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
                                rect, this,
                                AFX_IDW_PANE_FIRST + nView, &newContext);
        m_pViews [nView]->OnInitialUpdate();//?
    }
}
void getLocalIp(void)
{
    WSADATA wsaData;
    char name[155];
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
    {
        if(gethostname(name,sizeof(name)) == 0)
        {
            struct hostent* phe = gethostbyname(name);
            if (0 == phe)
            {
                return;
            }
            for (int i = 0; phe->h_addr_list[i] != 0; ++i)
            {
                struct in_addr addr;
                memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
                TRACE("IP %d:%s\n",i+1,inet_ntoa(addr));
            }
        }
        WSACleanup( );
    }
}



#include "StatusbarCtrl.h"
CMyStatusbarCtrl * statusbar = NULL;
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;
    /*g_testmultiReadtraffic_dlg = NULL;*/
    BOOL bNameValid;
    // set the visual manager and style based on persisted value
    OnApplicationLook(theApp.m_nAppLook);
    if (!m_wndMenuBar.Create(this))
    {
        TRACE0("Failed to create menubar\n");
        return -1;      // fail to create
    }
    m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

    // prevent the menu bar from taking the focus on activation
    SEND_COMMAND_DELAY_TIME = 100;





    CMFCPopupMenu::SetForceMenuFocus(FALSE);
    CMFCToolBar::SetSizes(CSize(32,32),CSize(32,32));
    CMFCToolBar::SetMenuSizes(CSize(32,32),CSize(24,24));

    UINT uiToolbarHotID;
    UINT uiToolbarColdID;
    UINT uiMenuID;
#if 0
    UINT uiToolbarHotID = theApp.m_bHiColorIcons ? IDB_BITMAP_V25049 : 0;
    UINT uiToolbarColdID = theApp.m_bHiColorIcons ? IDB_BITMAP_V25049 : 0;
    //theApp.m_bHiColorIcons=FALSE;
    UINT uiMenuID = theApp.m_bHiColorIcons ? IDB_MENUBAROWN_BITMAP : IDB_MENUBAROWN_BITMAP;//


    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
            !m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_VER25049 : IDR_TOOLBAR_VER25049,uiToolbarColdID, uiMenuID, FALSE /* Not locked */, 0, 0, uiToolbarHotID))

    {
        TRACE0("Failed to create toolbar\n");
        return -1;//fail to create
    }
#endif

    uiToolbarHotID =  IDB_BITMAP7 ;
    uiToolbarColdID = IDB_BITMAP7 ;
    uiMenuID =	IDB_BITMAP_BACNET_MENU_BIT ;//



    if (!m_testtoolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),IDR_TOOLBAR_BACNET) ||
            !m_testtoolbar.LoadToolBar(IDR_TOOLBAR_BACNET,uiToolbarColdID, uiMenuID, FALSE /* Not locked */, 0, 0, uiToolbarHotID))

    {
        TRACE0("Failed to create toolbar\n");
        return -1;//fail to create
    }


    ///////////////////////////////////////////////////////////////////////////////////

    if (!m_wndWorkSpace.Create (_T("Building View"), this, CRect (0, 0, 300, 800),
                                TRUE, ID_VIEW_WORKSPACE,
                                WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN  | CBRS_LEFT ))//| CBRS_FLOAT_MULTI
    {
        TRACE0("Failed to create Workspace bar\n");

        return FALSE;// fail to create
    }


    //////////////////////////////////////////////////////////////////////////////////
    CString strToolBarName;
    bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
    ASSERT(bNameValid);
    //m_wndToolBar.SetWindowText(strToolBarName);


    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    // Allow user-defined toolbars operations:
    InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);


    if (!m_wndStatusBar.Create(this)||!m_wndStatusBar.SetIndicators(indicators,
            sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    // TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
    //m_testtoolbar.EnableDocking(CBRS_ALIGN_ANY);

    //m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    //m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndWorkSpace.EnableDocking(CBRS_ALIGN_LEFT);


    EnableDocking(CBRS_ALIGN_ANY);

    DockPane(&m_wndMenuBar);
    //DockPane(&m_wndToolBar);
    DockPane (&m_wndWorkSpace);

    DockPane(&m_testtoolbar);
// 	int last=theApp.GetLanguage();
// 	theApp.m_locale.SetLanguage(last);
// 	g_language=last;
// 	gSetMenuStrings(m_hWnd);

    // enable Visual Studio 2005 style docking window behavior
    CDockingManager::SetDockingMode(DT_SMART);
    // enable Visual Studio 2005 style docking window auto-hide behavior
    EnableAutoHidePanes(CBRS_ALIGN_ANY);


    m_wndStatusBar.SetPaneInfo(0,ID_RW_INFO,SBPS_NOBORDERS,   300);
    // int index = m_wndStatusBar.CommandToIndex(ID_BUILDING_INFO);
    m_wndStatusBar.SetPaneInfo(1,ID_BUILDING_INFO,SBPS_NOBORDERS, 300);
    m_wndStatusBar.SetPaneInfo(2,ID_PROTOCOL_INFO,SBPS_STRETCH | SBPS_NOBORDERS , 0);
    m_wndStatusBar.SetPaneInfo(3,IDS_SHOW_RESULTS,SBPS_NOBORDERS , 1000);
    m_wndStatusBar.EnablePaneDoubleClick ();



    m_pTreeViewCrl=&m_wndWorkSpace.m_TreeCtrl;
    m_pTreeViewCrl->SetExtendedStyle(TVS_EDITLABELS, TVS_EDITLABELS);
    MainFram_hwd = this->m_hWnd;

    //  2011,7,4, 先判断是否第一次运行，是否要导入数据库。
    //ImportDataBaseForFirstRun();
    CString g_configfile_path =g_strExePth + g_strStartInterface_config;
    g_selected_serialnumber=GetPrivateProfileInt(_T("T3000_START"),_T("SerialNumber"),0,g_configfile_path);
    m_lastinterface=GetPrivateProfileInt(_T("T3000_START"),_T("Interface"),19,g_configfile_path);
    // 	//WrPrivateProfileInt(_T("Setting"),_T("Interface"),19,g_configfile_path);
    if (m_lastinterface != 19 && m_lastinterface!=24)
    {
        CString achive_file_path;
        CString temp_serial;
        temp_serial.Format(_T("%u.prg"),g_selected_serialnumber);
        achive_file_path = g_achive_folder + _T("\\") + temp_serial;
        Load_Product_Value_Cache(achive_file_path);
        g_tstat_id = product_register_value[6];
    }



    ScanTstatInDB();
    DeleteConflictInDB();//用于处理数据库中重复的数据，这些数据有相同的序列号;
    PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);

    SetTimer(MONITOR_MOUSE_KEYBOARD_TIMER,1000,NULL);
    SetTimer(REFRESH_TIMER, REFRESH_TIMER_VALUE, NULL);
    SetTimer(SAVE_PRODYCT_STATUS, 30000, NULL);

    m_pRefreshThread =(CRefreshTreeThread*) AfxBeginThread(RUNTIME_CLASS(CRefreshTreeThread));
    m_pRefreshThread->SetMainWnd(this);


    //tstat6
    Tstat6_func();//为TSTST6新寄存器用的。



    //检测Tstat6数据库中的这个表是否存在
    CString temptable = _T("Tstat6");
    CString tempsql = _T("create table Tstat6(Block TEXT,Address TEXT,Data TEXT,Description TEXT)");
    JudgeTstat6dbExist(temptable,tempsql);
    temptable = _T("Tstat7");
    tempsql = _T("create table Tstat7(Block TEXT,Address TEXT,Data TEXT,Description TEXT)");
    JudgeTstat6dbExist(temptable,tempsql);

    CString tempslider = _T("Sliderdb");
    CString tempsqlslider = _T("create table Sliderdb(Block Number,Address Number)");
    JudgeTstat6SliderExist(tempslider,tempsqlslider);

    //读取Sliderdb的值。
    ReadSlider();

    BuildingComportConfig();//用于 更改 Config里面的 Comport项;


//展开所有的项
//	Treestatus();
    HTREEITEM htiRoot = m_pTreeViewCrl->GetRootItem();//GetRootItem();
    m_pTreeViewCrl->Expand(htiRoot,TVE_EXPAND);
    HTREEITEM hChild = m_pTreeViewCrl->GetChildItem(htiRoot);

    //HTREEITEM GetChildItem(_In_ HTREEITEM hItem) const;
    m_pTreeViewCrl->Expand(hChild,TVE_EXPAND);
    HTREEITEM hChilder = m_pTreeViewCrl->GetChildItem(hChild);
    m_pTreeViewCrl->Expand(hChilder,TVE_EXPAND);

    HTREEITEM hChilder1 = m_pTreeViewCrl->GetChildItem(hChilder);
    m_pTreeViewCrl->Expand(hChilder1,TVE_EXPAND);


    hThread =CreateThread(NULL,NULL,Get_All_Dlg_Message,this,NULL, &nThreadID);
    hDeal_thread =CreateThread(NULL,NULL,Translate_My_Message,this,NULL, &nThreadID_Do);


    //Register热键
#ifdef _DEBUG //debug版本   
    int nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[0],MOD_ALT,'I');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + I failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[1],MOD_ALT,'O');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + O failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[2],MOD_ALT,'V');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + V failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[3],MOD_ALT,'P');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + P failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[5],MOD_ALT,'L');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + L failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[6],MOD_ALT,'G');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + G failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[7],MOD_ALT,'S');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + S failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[8],MOD_ALT,'H');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + H failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[9],MOD_ALT,'T');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + T failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[10],MOD_ALT,'A');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + A failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[11],MOD_ALT,'C');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + C failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[4],MOD_ALT,'R');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + R failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[12],MOD_ALT,'B');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + R failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[13],MOD_ALT,'D');
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey ALT + R failure"));

    nRet = RegisterHotKey(GetSafeHwnd(),1111,(MOD_SHIFT | MOD_CONTROL | MOD_ALT),'D'); //热键 ctrl + alt + shift + D
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey MOD_SHIFT + D failure"));
    nRet = RegisterHotKey(GetSafeHwnd(),1112,(MOD_SHIFT | MOD_CONTROL | MOD_ALT),'F'); //热键 ctrl + alt + shift + F
    if(!nRet)
        AfxMessageBox(_T("RegisterHotKey MOD_SHIFT + F failure"));
#else //release版本   
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[0],MOD_ALT,'I');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[1],MOD_ALT,'O');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[2],MOD_ALT,'V');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[3],MOD_ALT,'P');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[4],MOD_ALT,'R');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[5],MOD_ALT,'L');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[6],MOD_ALT,'G');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[7],MOD_ALT,'S');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[8],MOD_ALT,'H');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[9],MOD_ALT,'T');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[10],MOD_ALT,'A');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[11],MOD_ALT,'C');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[12],MOD_ALT,'B');
    RegisterHotKey(GetSafeHwnd(),m_MainHotKeyID[13],MOD_ALT,'D');
    RegisterHotKey(GetSafeHwnd(),1111,(MOD_SHIFT | MOD_CONTROL | MOD_ALT),'D');
    RegisterHotKey(GetSafeHwnd(),1112,(MOD_SHIFT | MOD_CONTROL | MOD_ALT),'F');
#endif
    for(int i=0; i<WINDOW_TAB_COUNT; i++)
    {
        pDialog[i]=NULL;
    }

    CString AutoFlashConfigPath;
    CString ApplicationFolder;
    GetModuleFileName(NULL, ApplicationFolder.GetBuffer(MAX_PATH), MAX_PATH);
    PathRemoveFileSpec(ApplicationFolder.GetBuffer(MAX_PATH));
    ApplicationFolder.ReleaseBuffer();
    AutoFlashConfigPath = ApplicationFolder + _T("//AutoFlashFile.ini");
    CFileFind fFind;
    if(fFind.FindFile(AutoFlashConfigPath))
    {
        DeleteFile(AutoFlashConfigPath);
    }

    MyRegAddress.MatchMoudleAddress();
    bac_net_initial_once = false;


#if 1
    //SOCKET soAck =::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    h_Broad=::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    BOOL bBroadcast=TRUE;
    ::setsockopt(h_Broad,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));
    int iMode=1;
    ioctlsocket(h_Broad,FIONBIO, (u_long FAR*) &iMode);

    BOOL bDontLinger = FALSE;
    setsockopt( h_Broad, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
    //SOCKADDR_IN bcast;
    h_bcast.sin_family=AF_INET;
    //bcast.sin_addr.s_addr=nBroadCastIP;
    h_bcast.sin_addr.s_addr=INADDR_BROADCAST;
    h_bcast.sin_port=htons(UDP_BROADCAST_PORT);

#endif


    /* m_file_firmware_Time=g_strExePth+_T("firmware\\Firmware_Time.ini");
     m_sFileToDownloadInto = g_strExePth;
     m_sFileToDownloadInto+=_T("firmware\\");
     CreateDirectory(m_sFileToDownloadInto,NULL);*/

    // 需要执行线程中的操作时

    if (m_lasttime_tree_node.protocol == Modbus_Serial)
    {
        open_com(m_lasttime_tree_node.ncomport);
        SetCommunicationType(0);
    }
    else  if(m_lasttime_tree_node.protocol == Modbus_TCP)
    {
        Open_Socket2(m_lasttime_tree_node.BuildingInfo.strIp,_wtoi(m_lasttime_tree_node.BuildingInfo.strIpPort));
        SetCommunicationType(1);
    }
    g_protocol =  m_lasttime_tree_node.protocol;

    int ReadID = read_one(g_tstat_id,6,10);

    if (ReadID > 0)
    {
        m_pTreeViewCrl->turn_item_image(m_lasttime_tree_node.product_item ,true);
        for (int i = 0; i<(int)m_product.size(); i++)
        {
            if (m_product.at(i).product_item == m_lasttime_tree_node.product_item)
            {

                m_product.at(i).status_last_time[0] = true;
                m_product.at(i).status_last_time[1] = true;
                m_product.at(i).status_last_time[2] = true;
            }

        }

    }
    else
    {
        m_pTreeViewCrl->turn_item_image(m_lasttime_tree_node.product_item ,false);
        for (int i = 0; i<(int)m_product.size(); i++)
        {
            if (m_product.at(i).product_item == m_lasttime_tree_node.product_item)
            {

                m_product.at(i).status_last_time[0] = false;
                m_product.at(i).status_last_time[1] = false;
                m_product.at(i).status_last_time[2] = false;
            }

        }
    }

    if(m_pDialogInfo==NULL)
    {
        m_pDialogInfo = new CDialogInfo;
        m_pDialogInfo->Create(IDD_DIALOG_INFO,this);
        m_pDialogInfo->ShowWindow(SW_HIDE);
        m_pDialogInfo->CenterWindow();
        m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T(""));
    }

    m_pFreshMultiRegisters = AfxBeginThread(_ReadMultiRegisters,this);
    m_pFreshTree=AfxBeginThread(_FreshTreeView, this);

#if 1
    nFlag = product_register_value[7];
    {
        if((nFlag == PM_TSTAT6) || (nFlag == PM_TSTAT7)|| (nFlag == PM_TSTAT5i)|| (nFlag == PM_TSTAT8) )
        {
            product_type =T3000_6_ADDRESS;
        }
        else if((nFlag == PM_TSTATRUNAR)||(nFlag == PM_TSTAT5E||nFlag == PM_PM5E) || (nFlag == PM_TSTAT5H)||(nFlag==PM_TSTAT5G))
        {
            product_type = T3000_5EH_LCD_ADDRESS;
        }
        else if((nFlag == PM_TSTAT5A) ||(nFlag == PM_TSTAT5B) ||
                (nFlag ==PM_TSTAT5C ) || (nFlag == PM_TSTAT5D) || (nFlag == PM_TSTAT5F))
        {
            product_type =T3000_5ABCDFG_LED_ADDRESS;
        }
        else if (nFlag==PM_CS_SM_AC||nFlag==PM_CS_SM_DC||nFlag==PM_CS_RSM_AC||nFlag==PM_CS_RSM_DC)
        {
            product_type=CS3000;
        }
        else if (nFlag==PM_T322AI||nFlag==PM_T38AI8AO6DO||nFlag==PM_T3PT10||nFlag==PM_T3IOA||nFlag==PM_T332AI||nFlag== PM_T38AI16O||nFlag==PM_T38I13O||nFlag==PM_T34AO||nFlag==PM_T36CT||nFlag==PM_T3PERFORMANCE)
        {
            product_type=T3000_T3_MODULES;
        }
        else
        {
            product_type=nFlag;
        }

        //Code and comments by Fance
        //Use old_product_type to save the last value.
        //if this value is change ,it will reload the register value.
        //example:
        //For tstats 5A : product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 185
        //For tstats 6	  product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 110
        if(old_product_type!=product_type)
        {
            old_product_type = product_type;
            MyRegAddress.Change_Register_Table();
        }

    }
    GetIONanme();
    if (product_type==T3000_6_ADDRESS)
    {
        LoadTstat_InputData();
        LoadTstat_OutputData();
    }
    //int const PM_CO2_NET = 32;
    // int const PM_CO2_RS485 = 33;
    else if (product_type==CS3000)
    {
        LoadInputData_CS3000();
        LoadOutputData_CS3000();
    }

    else if (product_type == T3000_T3_MODULES)
    {


    }

#endif
    //m_pThread =NULL;// AfxBeginThread(_DownloadThread, this, THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED);
// 		if (m_pThread == NULL)
// 		{
// 			TRACE(_T("Failed to create download thread, dialog is aborting\n"));
//
// 		}
    PostMessage(WM_CREATE_STATUSBAR,0,0);
    CString image_fordor;
    image_fordor = ApplicationFolder + _T("\\Database\\Buildings\\") + m_strCurMainBuildingName + _T("\\image");
    CFileFind temp_find;
    if(temp_find.FindFile(image_fordor) == 0)
    {
        CreateDirectory(image_fordor,NULL);
    }

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWndEx::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs


    return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
    CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
    pDlgCust->EnableUserDefinedToolbars();
    pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
    LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
    if (lres == 0)
    {
        return 0;
    }

    CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
    ASSERT_VALID(pUserToolbar);

    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
    CWaitCursor wait;

    theApp.m_nAppLook = id;

    switch (theApp.m_nAppLook)
    {
    case ID_VIEW_APPLOOK_WIN_2000:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
        break;

    case ID_VIEW_APPLOOK_OFF_XP:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
        break;

    case ID_VIEW_APPLOOK_WIN_XP:
        CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
        break;

    case ID_VIEW_APPLOOK_OFF_2003:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
        CDockingManager::SetDockingMode(DT_SMART);
        break;

    case ID_VIEW_APPLOOK_VS_2005:
        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
        CDockingManager::SetDockingMode(DT_SMART);
        break;

    default:
        switch (theApp.m_nAppLook)
        {
        case ID_VIEW_APPLOOK_OFF_2007_BLUE:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_BLACK:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_SILVER:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
            break;

        case ID_VIEW_APPLOOK_OFF_2007_AQUA:
            CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
            break;
        }

        CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
        CDockingManager::SetDockingMode(DT_SMART);
    }
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
    theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}
void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
    pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
    // base class does the real work

    if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
    {
        return FALSE;
    }
    // enable customization button for all user toolbars
    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);

    for (int i = 0; i < iMaxUserToolbars; i ++)
    {
        CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
        if (pUserToolbar != NULL)
        {
            pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
        }
    }

    return TRUE;
}


void CMainFrame::OnCheckBuildingBar()
{
    ShowPane (&m_wndWorkSpace, (m_wndWorkSpace.GetStyle () & WS_VISIBLE) == 0, FALSE, TRUE);

}
void CMainFrame::OnUpdateCheckBuildingBar(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck (m_wndWorkSpace.IsWindowVisible ());
}
void CMainFrame::OnCheckIOPane()
{
}
void CMainFrame::OnUpdateCheckIOPane(CCmdUI* pCmdUI)
{

}

void CMainFrame::OnHTreeItemSeletedChanged(NMHDR* pNMHDR, LRESULT* pResult)
{



    g_bPauseRefreshTree = TRUE;
    Flexflash = TRUE;
    HTREEITEM hSelItem;//=m_pTreeViewCrl->GetSelectedItem();
//   int nRet =read_one(g_tstat_id,6,1);

    CPoint pt;
    GetCursorPos(&pt);
    m_pTreeViewCrl->ScreenToClient(&pt);
    hSelItem = m_pTreeViewCrl->HitTest(pt);
    if(hSelItem == NULL)
        return;
    RECT r;


    //////////////////////////////////////////////////////////////////////////
    m_strCurSelNodeName = m_pTreeViewCrl->GetItemText(hSelItem);
    BeginWaitCursor();
    //CM5
    g_bChamber=FALSE;
    m_isMiniPanel=FALSE;
    CString g_strT3000LogString;
    g_bPauseMultiRead=TRUE;
#if 1
    for(UINT i=0; i<m_product.size(); i++)
    {
        if(hSelItem==m_product.at(i).product_item )
        {
            /*  int const PM_CS_SM_AC = 36;
              int const PM_CS_SM_DC = 37;
              int const PM_CS_RSM_AC = 38;
              int const PM_CS_RSM_DC = 39;*/

            CString Product_Custom = m_product.at(i).Custom;
            m_current_tree_node = m_product.at(i);
            if (Product_Custom.CompareNoCase(_T("1")) == 0 ||
                    m_current_tree_node.product_class_id == PM_CS_SM_AC||
                    m_current_tree_node.product_class_id == PM_CS_SM_DC||
                    m_current_tree_node.product_class_id == PM_CS_RSM_AC||
                    m_current_tree_node.product_class_id == PM_CS_RSM_DC
               )
            {
                g_tstat_id = m_product.at(i).product_id;
                g_selected_serialnumber = m_product.at(i).serial_number;
                SwitchToPruductType(DLG_DIALOG_CUSTOM_VIEW);
                return;
            }

            g_strT3000LogString.Format(_T("Trying to connect to %s:%d"),GetProductName(m_product.at(i).product_class_id),m_product.at(i).serial_number);


            CString* pstrInfo = new CString(g_strT3000LogString);
            ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));
            if(m_product.at(i).product_class_id == PM_CM5)
            {
                g_tstat_id=m_product.at(i).product_id;
                //SetPaneString(2,_T("Connect To CM5"));
                m_isCM5=TRUE;

                DoConnectToANode(hSelItem);
                //SwitchToPruductType(4);
            }
            else if (m_product.at(i).product_class_id == PM_MINIPANEL)
            {
                g_tstat_id = m_product.at(i).product_id;
                m_isMiniPanel=TRUE;
                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id == PM_T3IOA)
            {
                g_tstat_id = m_product.at(i).product_id;
                DoConnectToANode(hSelItem);

            }

            else if (m_product.at(i).product_class_id == PM_T38I13O)
            {
                g_tstat_id = m_product.at(i).product_id;
                /*SwitchToPruductType(DLG_DIALOGT38I13O_VIEW);*/
                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id == PM_T34AO) //T3
            {
                g_tstat_id = m_product.at(i).product_id;
                /*SwitchToPruductType(DLG_DIALOGT3_VIEW);*/
                DoConnectToANode(hSelItem);

            }
            else if (m_product.at(i).product_class_id == PM_T322AI) //T3
            {
                g_tstat_id = m_product.at(i).product_id;
                /*SwitchToPruductType(DLG_DIALOGT3_VIEW);*/
                DoConnectToANode(hSelItem);

            }
            else if (m_product.at(i).product_class_id == PM_T38AI8AO6DO) //T3
            {
                g_tstat_id = m_product.at(i).product_id;
                /*SwitchToPruductType(DLG_DIALOGT3_VIEW);*/
                DoConnectToANode(hSelItem);

            }
            else if (m_product.at(i).product_class_id == PM_T3PT10)
            {
                g_tstat_id = m_product.at(i).product_id;
                /* SwitchToPruductType(DLG_DIALOGT3PT10);*/
                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id==PM_T332AI)
            {
                g_tstat_id = m_product.at(i).product_id;
                /*	SwitchToPruductType(DLG_DIALOGT332AI_VIEW);*/

                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id ==PM_AirQuality) //AirQuality
            {
                g_tstat_id = m_product.at(i).product_id;
                //SwitchToPruductType(DLG_AIRQUALITY_VIEW);
                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id == PM_LightingController)//LightingController
            {
                g_tstat_id = m_product.at(i).product_id;
                if(m_product.at(i).BuildingInfo.hCommunication==NULL||m_strCurSubBuldingName.CompareNoCase(m_product.at(i).BuildingInfo.strBuildingName)!=0)
                {
                    //connect:
                    BOOL bRet = ConnectSubBuilding(m_product.at(i).BuildingInfo);
                    if (!bRet)
                    {
                        if(m_product.at(i).BuildingInfo.strProtocol.CompareNoCase(_T("Modbus TCP")) == 0) // net work protocol
                        {
                            CheckConnectFailure(m_product.at(i).BuildingInfo.strIp);
                        }
                    }
                }
                SwitchToPruductType(DLG_LIGHTINGCONTROLLER_VIEW);
            }
            else if (m_product.at(i).product_class_id==PM_TSTAT6_HUM_Chamber)
            {

                //g_bChamber=TRUE;
                g_tstat_id = m_product.at(i).product_id;

                //SwitchToPruductType(DLG_HUMCHAMBER);
                DoConnectToANode(hSelItem);
            }
            else if (m_product.at(i).product_class_id==PM_T38I13O)
            {
                g_tstat_id=m_product.at(i).product_id;
                DoConnectToANode(hSelItem);

            }
            else if (m_product.at(i).product_class_id==PM_T36CT)
            {
                g_tstat_id = m_product.at(i).product_id;
                DoConnectToANode(hSelItem);
                /*SwitchToPruductType(DLG_DIALOGT36CT);*/
            }
            else
            {
                g_tstat_id = m_product.at(i).product_id;
                DoConnectToANode(hSelItem);
            }

        }
    }
#endif
    g_bPauseMultiRead=FALSE;

    EndWaitCursor();
    g_bPauseRefreshTree = FALSE;

}


void CMainFrame::OnHTreeItemEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{


}

LRESULT CMainFrame::OnHTreeItemBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{

    return 0;
}

void  CMainFrame::OnHTreeMessageSeletedChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    //if(list_mouse_click)
    //{
    //	list_mouse_click = true;
    //}
    //OnHTreeItemSeletedChanged( pNMHDR, pResult);
    //list_mouse_click = false;
}

void  CMainFrame::OnHTreeItemClick(NMHDR *pNMHDR, LRESULT *pResult)
{
    if(list_mouse_click)
    {
        list_mouse_click = true;
    }
    OnHTreeItemSeletedChanged(pNMHDR, pResult);
    list_mouse_click = false;
}
//
//BOOL CMainFrame::ValidAddress(CString sAddress)
//{
//	int nPos;
//	UINT n1,n2,n3,n4;
//	CString sTemp=sAddress;
//	n1=_wtoi(sTemp);
//	nPos=sTemp.Find(_T("."));
//	if(nPos==-1) return false;
//	sTemp=sTemp.Mid(nPos+1);
//	n2=_wtoi(sTemp);
//	nPos=sTemp.Find(_T("."));
//	if(nPos==-1) return false;
//	sTemp=sTemp.Mid(nPos+1);
//	n3=_wtoi(sTemp);
//	nPos=sTemp.Find(_T("."));
//	if(nPos==-1) return false;
//	sTemp=sTemp.Mid(nPos+1);
//	n4=_wtoi(sTemp);
//	if(n1<0 ||n1>255) return false;
//	if(n2<0 ||n2>255) return false;
//	if(n3<0 ||n3>255) return false;
//	if(n4<0 ||n4>255) return false;
//	return TRUE;
//}
BOOL CMainFrame::ValidAddress(CString sAddress,UINT& n1,UINT& n2,UINT& n3,UINT& n4)
{
    int nPos;
    CString sTemp=sAddress;
    n1=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);
    n2=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);
    n3=_wtoi(sTemp);
    nPos=sTemp.Find(_T("."));
    if(nPos==-1) return false;
    sTemp=sTemp.Mid(nPos+1);
    n4=_wtoi(sTemp);
    if(n1<0 ||n1>255) return false;
    if(n2<0 ||n2>255) return false;
    if(n3<0 ||n3>255) return false;
    if(n4<0 ||n4>255) return false;
    return true;
}

//删除数据库中 重叠的device.;
void CMainFrame::DeleteConflictInDB()
{
    bool find_conflict = false;
    int temp_item_count = (int)m_product.size();
    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();

    for (int i=0; i<temp_item_count; i++)
    {
        for (int j=i+1; j<temp_item_count; j++)
        {
            if(m_product.at(i).serial_number == m_product.at(j).serial_number)
            {
                find_conflict = true;

                CString mtemp_serial_number;
                CString strSql;
                mtemp_serial_number.Format(_T("%u"),m_product.at(i).serial_number);
                try
                {
                    strSql.Format(_T("delete * from ALL_NODE where Serial_ID ='%s'"), mtemp_serial_number);
                    bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
                }
                catch(_com_error *e)
                {
                    //AfxMessageBox(e->ErrorMessage());
                }


                break;
            }
        }
    }
    bado.CloseConn();
    if(find_conflict)
        PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);
}



void CMainFrame::LoadProductFromDB()
{
    ClearBuilding();
    CADO ado;
    ado.OnInitADOConn();
    m_product.clear();
    CString strSql;
    strSql.Format(_T("select * from Building where Default_SubBuilding=-1"));
    ado.m_pRecordset=ado.OpenRecordset(strSql);
    int count =ado.GetRecordCount(ado.m_pRecordset);
    _variant_t temp_variant;
    if(count<=0)
    {
        ado.CloseRecordset();
        ado.CloseConn();
        AfxMessageBox(_T("There is no default building, please select a building Firstly!"));
        return;
    }

    m_strCurMainBuildingName=ado.m_pRecordset->GetCollect("Main_BuildingName");
    CString cs_temp_protocol;
    CString cs_temp_baudrate;
    temp_variant=ado.m_pRecordset->GetCollect("Protocal");//
    if(temp_variant.vt!=VT_NULL)
        cs_temp_protocol=temp_variant;
    else
    {
        cs_temp_protocol=_T("Auto");
        strSql.Format(_T("update Building set Protocal='Auto' where Main_BuildingName ='%s'"), m_strCurMainBuildingName);
        ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
    }

    if(cs_temp_protocol.CompareNoCase(_T("Modbus 485")) == 0 )
    {
        current_building_protocol = P_MODBUS_485;
    }
    else if(cs_temp_protocol.CompareNoCase(_T("Modbus TCP")) == 0 )
    {
        current_building_protocol = P_MODBUS_TCP;
    }
    else if(cs_temp_protocol.CompareNoCase(_T("Bacnet MSTP")) == 0 )
    {
        current_building_protocol = P_BACNET_MSTP;
    }
    else if(cs_temp_protocol.CompareNoCase(_T("Bacnet IP")) == 0 )
    {
        current_building_protocol = P_REMOTE_DEVICE;
    }
    else
    {
        current_building_protocol = P_AUTO;
    }

    CString StrComport;
    CString StrBaudrate;


    CString StrIp;
    if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP))
    {


        temp_variant=ado.m_pRecordset->GetCollect("Braudrate");//
        if(temp_variant.vt!=VT_NULL)
        {
            cs_temp_baudrate = temp_variant;
        }
        else
        {
            cs_temp_protocol=_T("19200");
            strSql.Format(_T("update Building set Braudrate='19200' where Main_BuildingName ='%s'"), m_strCurMainBuildingName);
            ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
        }

        current_building_baudrate = _wtoi(cs_temp_baudrate);
        if((current_building_baudrate!= 19200) && (current_building_baudrate != 9600) && (current_building_baudrate != 38400))
        {
            current_building_baudrate = 19200;
        }

        //current_building_comport
        temp_variant = ado.m_pRecordset->GetCollect(_T("Com_Port"));
        if(temp_variant.vt!=VT_NULL)
        {
            StrComport=temp_variant;
            current_building_comport = _wtoi(StrComport.Mid(3));
        }
        else
        {
            current_building_comport=-1;
        }

    }
    if (current_building_protocol == P_MODBUS_TCP || current_building_protocol == P_BACNET_IP || current_building_protocol == P_REMOTE_DEVICE)
    {
        temp_variant=ado.m_pRecordset->GetCollect("Ip_Address");//
        if(temp_variant.vt!=VT_NULL)
        {
            StrIp = temp_variant;
            m_str_curBuilding_Domain_IP = StrIp;
        }
        else
        {
            m_str_curBuilding_Domain_IP.Empty();
        }

    }
    else
        m_str_curBuilding_Domain_IP.Empty();
    /*if(m_pRs->State)
    m_pRs->Close();*/
    ado.CloseRecordset();
    m_subNetLst.clear();

    strSql.Format(_T("select * from Building where Main_BuildingName ='%s'"),m_strCurMainBuildingName);
    //m_pRs->Open(_variant_t(strSql),_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);
    ado.m_pRecordset=ado.OpenRecordset(strSql);
    m_nCurSubBuildingIndex=-1;
    int nTemp=-1;
    while(VARIANT_FALSE==ado.m_pRecordset->EndOfFile)
    {
        nTemp++;
        int nDefault=0;
        Building_info temBuildingInfo;
        //memset(&temBuildingInfo,0,sizeof(temBuildingInfo));
        temp_variant=ado.m_pRecordset->GetCollect("Building_Name");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strBuildingName=temp_variant;
        else
            temBuildingInfo.strBuildingName=_T("");



        temp_variant=ado.m_pRecordset->GetCollect("Protocal");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strProtocol=temp_variant;
        else
            temBuildingInfo.strProtocol=_T("");

        temp_variant=ado.m_pRecordset->GetCollect("Ip_Address");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strIp=temp_variant;
        else
            temBuildingInfo.strIp=_T("");


        temp_variant=ado.m_pRecordset->GetCollect("Com_Port");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strComPort=temp_variant;
        else
            temBuildingInfo.strComPort=_T("");


        temp_variant=ado.m_pRecordset->GetCollect("Ip_Port");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strIpPort=temp_variant;
        else
            temBuildingInfo.strIpPort=_T("");




        temBuildingInfo.hCommunication=NULL;

        temp_variant=ado.m_pRecordset->GetCollect("Main_BuildingName");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strMainBuildingname=temp_variant;
        else
            temBuildingInfo.strMainBuildingname=temp_variant;



        temp_variant=ado.m_pRecordset->GetCollect("Braudrate");//
        if(temp_variant.vt!=VT_NULL)
            temBuildingInfo.strBaudRate=temp_variant;
        else
            temBuildingInfo.strBaudRate=_T("");



        CString Building_DBpath;
        nDefault=ado.m_pRecordset->GetCollect("Default_SubBuilding");
        if(nDefault==-1)
        {
            m_nCurSubBuildingIndex=nTemp;
        }
        Building_DBpath=ado.m_pRecordset->GetCollect("Building_Path");

        int index= Building_DBpath.Find(_T("Database"));
        Building_DBpath.Delete(0,index);

        g_strCurBuildingDatabasefilePath=GetExePath(true)+  Building_DBpath;



        //nDefault=ado.m_pRecordset->GetCollect("Default_SubBuilding");
        //if(nDefault==-1)
        //{
        //	m_nCurSubBuildingIndex=nTemp;
        //}
        //g_strCurBuildingDatabasefilePath=ado.m_pRecordset->GetCollect("Building_Path");

        ado.m_pRecordset->MoveNext();
        m_subNetLst.push_back(temBuildingInfo);
    }
    if(m_subNetLst.size()<=0)
        AfxMessageBox(_T("There is no default building,please select a building First！"));

    ado.CloseRecordset();

    TV_INSERTSTRUCT tvInsert;////added

    m_strCurSubBuldingName=m_subNetLst.at(m_nCurSubBuildingIndex).strBuildingName;

    CString strBuilding=m_strCurSubBuldingName;//m_subNetLst.at(k).strBuildingName;

    tvInsert.hParent = TVI_ROOT; // 指定父句柄
    tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
    tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strBuilding;
    tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
    TVINSERV_BUILDING
    HTREEITEM hTreeSubbuilding=NULL;
    hTreeSubbuilding=m_pTreeViewCrl->InsertSubnetItem(&tvInsert);//插入subbuilding。
    // Expand the parent, if possible.
    HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hTreeSubbuilding);
    if (hParent != NULL)
        m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);



    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();
    HTREEITEM hlocalnetwork=NULL;
    if((current_building_protocol == P_MODBUS_TCP) || (current_building_protocol == P_AUTO))
    {
        CString strNetWrokName= _T("Local Network");
        ///*********tree***********************************
        tvInsert.hParent = hTreeSubbuilding; // 指定父句柄
        tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象

        tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strNetWrokName;
        tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
        TVINSERV_FLOOR


        hlocalnetwork=m_pTreeViewCrl->InsertItem(&tvInsert);//返回楼层的句柄
    }
    HTREEITEM hrootserialport=NULL;
    if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP) || (current_building_protocol == P_AUTO))
    {
        CString strSerialRootName= _T("Serial Port");
        ///*********tree***********************************
        tvInsert.hParent = hTreeSubbuilding; // 指定父句柄
        tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象

        tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strSerialRootName;
        tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
        TVINSERV_FLOOR


        hrootserialport=m_pTreeViewCrl->InsertItem(&tvInsert);
    }

    if((current_building_protocol == P_REMOTE_DEVICE)|| (current_building_protocol == P_AUTO))
    {
        CString strRemoteNetworkName= _T("Remote Network Device");
        ///*********tree***********************************
        tvInsert.hParent = hTreeSubbuilding; // 指定父句柄
        tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象

        tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strRemoteNetworkName;
        tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
        TVINSERV_FLOOR

        HTREEITEM hrootremote=NULL;
        hrootremote=m_pTreeViewCrl->InsertItem(&tvInsert);
    }


    const int COM_SERIAL_PORT = 0;
    const int LOCAL_NETWORK_PORT = 1;
    for (int z=0; z<3; z++)
    {
        int nTemp3;
        CString PortName;
        CString temp_show;
        HTREEITEM hcomport=NULL;
        if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP) || (current_building_protocol == P_AUTO))
        {
            if(z == COM_SERIAL_PORT)
            {
                strSql.Format(_T("select DISTINCT Com_Port from ALL_NODE where Building_Name = '%s' ORDER BY Com_Port ASC"),strBuilding);
                bado.m_pRecordset=bado.OpenRecordset(strSql);
                nTemp3 = bado.GetRecordCount(bado.m_pRecordset);
                while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)//所有楼层。
                {
                    PortName= bado.m_pRecordset->GetCollect("Com_Port");
                    int comport_value = _wtoi(PortName);
                    if(comport_value > 50)
                    {
                        bado.m_pRecordset->MoveNext();
                        continue;
                    }

                    temp_show = _T("Com") + PortName;
                    tvInsert.hParent = hrootserialport; // 指定父句柄
                    tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象

                    tvInsert.item.pszText = (LPTSTR)(LPCTSTR)temp_show;
                    tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
                    TVINSERV_FLOOR


                    hcomport=m_pTreeViewCrl->InsertItem(&tvInsert);

                    _com_port_tree m_comport_temp;
                    m_comport_temp.building_item=hTreeSubbuilding;
                    m_comport_temp.serial_port_item =hrootserialport;
                    m_comport_temp.each_port_item = hcomport;
                    m_comport_temp.strComPortName=PortName;
                    m_comportlist.push_back(m_comport_temp);
                    bado.m_pRecordset->MoveNext();
                }
                bado.CloseRecordset();
            }

            m_pTreeViewCrl->Expand(hrootserialport, TVE_EXPAND);

            int loop_count = 0;
            if(z == COM_SERIAL_PORT)
            {
                loop_count = m_comportlist.size();
            }
            else if(z == LOCAL_NETWORK_PORT)
            {
                loop_count = 1;
            }

            for (int j=0; j<loop_count; j++)
            {
                CString temp_cs;
                CString temp_parent_serialnum;
                if(z == COM_SERIAL_PORT)
                {
                    temp_cs = m_comportlist.at(j).strComPortName;
                    strSql.Format(_T("select * from ALL_NODE where Building_Name = '%s' and Com_Port = '%s'"),strBuilding,temp_cs);
                }
                else if(z == LOCAL_NETWORK_PORT)
                {
                    strSql.Format(_T("select * from ALL_NODE where Building_Name = '%s'"),strBuilding);
                }

                bado.m_pRecordset=bado.OpenRecordset(strSql);
                int temp_count = bado.GetRecordCount(bado.m_pRecordset);
                if(temp_count > 0)
                {
                    while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)//次Com port 下面的所有 设备;
                    {
                        if(z == LOCAL_NETWORK_PORT)
                        {
                            PortName= bado.m_pRecordset->GetCollect("Com_Port");
                            int comport_value = _wtoi(PortName);
                            if(comport_value <= 50)
                            {
                                bado.m_pRecordset->MoveNext();
                                continue;
                            }
                        }

                        temp_variant=bado.m_pRecordset->GetCollect("Parent_SerialNum");
                        if(temp_variant.vt!=VT_NULL)
                            temp_parent_serialnum=temp_variant;
                        else
                            temp_parent_serialnum=_T("");
                        unsigned int temp_int_serial;
                        temp_int_serial = (unsigned int)_wtoi(temp_parent_serialnum);
                        if((!temp_parent_serialnum.IsEmpty()) && (temp_int_serial != 0))	//说明有父节点;先插入父节点
                        {
                            bado.m_pRecordset->MoveNext();
                            continue;
                        }

                        CString strProdcut=bado.m_pRecordset->GetCollect("Product_name");
                        if(z == COM_SERIAL_PORT)
                        {
                            tvInsert.hParent = m_comportlist.at(j).each_port_item ; // 指定父句柄
                        }
                        else if(z == LOCAL_NETWORK_PORT)
                        {
                            tvInsert.hParent = hlocalnetwork;// 指定父句柄 为本地网络;
                        }
                        tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
                        tvInsert.item.pszText =(LPTSTR)(LPCTSTR) strProdcut;
                        //TRACE(strProdcut);
                        tvInsert.hInsertAfter =TVI_SORT;// TVI_LAST; // 项目插入方式
                        int temp_product_class_id=bado.m_pRecordset->GetCollect("Product_class_ID");
                        if(temp_product_class_id==PM_NC)
                            TVINSERV_NET_WORK
                            else if(temp_product_class_id==LED_PRODUCT_MODEL)
                                TVINSERV_LED
                                else if(temp_product_class_id==PM_SOLAR)
                                    TVINSERV_SOLAR
                                    else if (temp_product_class_id == PM_CM5 ) //CM5
                                        TVINSERV_CMFIVE
                                        else if (temp_product_class_id == PM_T3PT10||
                                                 temp_product_class_id == PM_T3IOA||
                                                 temp_product_class_id == PM_T332AI||
                                                 temp_product_class_id ==  PM_T38AI16O||
                                                 temp_product_class_id == PM_T38I13O||
                                                 temp_product_class_id == PM_T34AO||
                                                 temp_product_class_id == PM_T36CT||
                                                 temp_product_class_id == PM_T322AI||
                                                 temp_product_class_id == PM_T38AI8AO6DO) //T3
                                            TVINSERV_NET_WORK
                                            else if (temp_product_class_id ==PM_MINIPANEL )//Mini Panel
                                                TVINSERV_MINIPANEL
                                                else if (temp_product_class_id == PM_AirQuality) //AirQuality
                                                    TVINSERV_TSTAT6
                                                    else if (temp_product_class_id == PM_LightingController)//Lightingcontroller
                                                        TVINSERV_LC          //tree0412
                                                        else if (temp_product_class_id == PM_TSTAT7)//TSTAT7 &TSTAT6 //tree0412
                                                            TVINSERV_LED //tree0412
                                                            else if(temp_product_class_id == PM_TSTAT6||temp_product_class_id == PM_TSTAT7||temp_product_class_id == PM_TSTAT5i||temp_product_class_id == PM_TSTAT8)
                                                                TVINSERV_TSTAT6
                                                                else if((temp_product_class_id == PM_CO2_NET) || (temp_product_class_id == PM_CO2_RS485)||(temp_product_class_id == PM_PRESSURE_SENSOR))
                                                                    TVINSERV_CO2
                                                                    else if (temp_product_class_id == PM_CS_SM_AC||temp_product_class_id == PM_CS_SM_DC||temp_product_class_id == PM_CS_RSM_AC||temp_product_class_id == PM_CS_RSM_DC)
                                                                    {
                                                                        TVINSERV_CS3000
                                                                    }
                                                                    else

                                                                        TVINSERV_TSTAT

                                                                        HTREEITEM hProductItem=m_pTreeViewCrl->InsertItem(&tvInsert);

                        HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hProductItem);
                        if (hParent != NULL)
                            m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);

                        tree_product m_product_temp;
                        m_product_temp.product_item  =hProductItem;

                        temp_variant=bado.m_pRecordset->GetCollect("Serial_ID");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");

                        long temp_serial_id = (long)(_wtoi64(strSql));
                        unsigned int correct_id = (DWORD)(_wtoi64(strSql));
                        //用于将以前数据库中的 负的序列号 修改为正的;Add by Fance
                        if(temp_serial_id < 0)
                        {
                            CString wrong_serial_id;
                            wrong_serial_id = strSql;
                            CString correct_serial_id;
                            CString str_temp;
                            correct_serial_id.Format(_T("%u"),correct_id);
                            try
                            {
                                str_temp.Format(_T("update ALL_NODE set Serial_ID ='%s' where Serial_ID = '%s'"),correct_serial_id, wrong_serial_id);
                                bado.m_pConnection->Execute(str_temp.GetString(),NULL,adCmdText);
                            }
                            catch(_com_error *e)
                            {
                                AfxMessageBox(e->ErrorMessage());
                            }
                        }
                        m_product_temp.serial_number= correct_id;

                        temp_variant=bado.m_pRecordset->GetCollect("Product_ID");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.product_id=_wtoi(strSql);

                        temp_variant=bado.m_pRecordset->GetCollect("NetworkCard_Address");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.NetworkCard_Address=strSql;
                        temp_variant=bado.m_pRecordset->GetCollect("Product_class_ID");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.product_class_id=_wtoi(strSql);
                        temp_variant=bado.m_pRecordset->GetCollect("Hardware_Ver");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.hardware_version=(float)_wtof(strSql);

                        temp_variant=bado.m_pRecordset->GetCollect("Software_Ver");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.software_version=(float)_wtof(strSql);

                        temp_variant=bado.m_pRecordset->GetCollect("EPsize");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.nEPsize=(int)_wtol(strSql);

                        temp_variant=bado.m_pRecordset->GetCollect("Protocol");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        m_product_temp.protocol = (int)_wtoi(strSql);

                        temp_variant=bado.m_pRecordset->GetCollect("Bautrate");//
                        if(temp_variant.vt!=VT_NULL)
                            strSql=temp_variant;
                        else
                            strSql=_T("");
                        if(_wtoi(strSql) !=0)
                            m_product_temp.baudrate = _wtoi(strSql);
                        else
                            m_product_temp.baudrate = 19200;
                        if(m_product_temp.protocol == PROTOCOL_BACNET_IP)
                        {
                            char cTemp1[255];
                            memset(cTemp1,0,255);
                            WideCharToMultiByte( CP_ACP, 0, strSql.GetBuffer(), -1, cTemp1, 255, NULL, NULL );
                            DWORD dwIP = inet_addr(cTemp1);

                            m_product_temp.baudrate=dwIP;//_wtoi(strTemp);
                        }
                        else
                            m_product_temp.baudrate=_wtoi(strSql);
                        if (m_product_temp.product_class_id == PM_NC)
                        {
                            m_product_temp.baudrate = 19200;
                        }
                        ////
                        temp_variant=bado.m_pRecordset->GetCollect("Online_Status");//
                        if(temp_variant.vt!=VT_NULL)
                        {
                            m_product_temp.status = temp_variant;
                            m_product_temp.status_last_time[0] = m_product_temp.status;
                            m_product_temp.status_last_time[1] = false;
                            m_product_temp.status_last_time[2] = false;
                        }
                        else
                        {
                            m_product_temp.status = false;
                            m_product_temp.status_last_time[0] = false;
                            m_product_temp.status_last_time[1] = false;
                            m_product_temp.status_last_time[2] = false;
                        }
                        temp_variant=bado.m_pRecordset->GetCollect("Custom");//
                        if(temp_variant.vt!=VT_NULL)
                            m_product_temp.Custom=temp_variant;
                        else
                            m_product_temp.Custom=_T("");

                        temp_variant=bado.m_pRecordset->GetCollect("Product_name");//
                        if(temp_variant.vt!=VT_NULL)
                        {
                            m_product_temp.NameShowOnTree = temp_variant;
                        }
                        else
                        {
                            m_product_temp.NameShowOnTree = _T("");

                        }


                        m_product_temp.BuildingInfo=m_subNetLst.at(m_nCurSubBuildingIndex);
                        //20120423
                        if(((strSql.CompareNoCase(_T("19200")) == 0)) || (strSql.CompareNoCase(_T("9600")) == 0) || ((strSql.CompareNoCase(_T("38400")) == 0)))
                        {
                            m_product_temp.BuildingInfo.strIp.Empty();
                            m_product_temp.BuildingInfo.strBaudRate = strSql;
                        }
                        else
                        {
                            m_product_temp.BuildingInfo.strIp = strSql;
                        }

                        temp_variant=bado.m_pRecordset->GetCollect("Com_Port");//
                        if(temp_variant.vt!=VT_NULL)
                        {
                            strSql=temp_variant;
                            m_product_temp.ncomport = _wtoi(strSql);
                        }
                        else
                        {
                            strSql=_T("");
                            m_product_temp.ncomport = 0;
                        }
                        m_product_temp.BuildingInfo.strIpPort = _T("10000");
                        temp_variant=bado.m_pRecordset->GetCollect("Background_imgID");
                        if(temp_variant.vt!=VT_NULL)
                            m_product_temp.strImgPathName=temp_variant;
                        else
                            m_product_temp.strImgPathName=_T("");


                        temp_variant=bado.m_pRecordset->GetCollect("Parent_SerialNum");
                        if(temp_variant.vt!=VT_NULL)
                        {
                            CString temp_value1;
                            temp_value1 = temp_variant;
                            m_product_temp.note_parent_serial_number=(unsigned int)_wtoi(temp_value1);
                        }
                        else
                            m_product_temp.note_parent_serial_number=0;



                        temp_variant=bado.m_pRecordset->GetCollect("Panal_Number");
                        if(temp_variant.vt!=VT_NULL)
                        {
                            CString temp_value1;
                            temp_value1 = temp_variant;
                            m_product_temp.panel_number=(unsigned char)_wtoi(temp_value1);
                        }
                        else
                            m_product_temp.panel_number=0;

                        temp_variant=bado.m_pRecordset->GetCollect("Object_Instance");
                        if(temp_variant.vt!=VT_NULL)
                        {
                            CString temp_value1;
                            temp_value1 = temp_variant;
                            m_product_temp.object_instance=(unsigned int)_wtoi(temp_value1);
                        }
                        else
                            m_product_temp.object_instance=0;


                        m_product.push_back(m_product_temp);
                        bado.m_pRecordset->MoveNext();

                    }
                }
                bado.CloseRecordset();

                if(z == COM_SERIAL_PORT)
                {
                    strSql.Format(_T("select * from ALL_NODE where Building_Name = '%s' and Com_Port = '%s' and Parent_SerialNum <> '0' and Parent_SerialNum <> ''"),strBuilding,temp_cs);
                }
                else if(z == LOCAL_NETWORK_PORT)
                {
                    strSql.Format(_T("select * from ALL_NODE where Building_Name = '%s' and Parent_SerialNum <> '0' and Parent_SerialNum <> ''"),strBuilding);
                }

                bado.m_pRecordset=bado.OpenRecordset(strSql);
                int temp_child_note_count = bado.GetRecordCount(bado.m_pRecordset);
                if(temp_child_note_count > 0)//就说明这个节点下面有 挂在父节点下面的;
                {
                    while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)
                    {
                        CString cs_parents_serial_number;
                        unsigned int uint_p_serial_number;
                        cs_parents_serial_number=bado.m_pRecordset->GetCollect("Parent_SerialNum");
                        uint_p_serial_number = _wtoi(cs_parents_serial_number);
                        bool find_parents = false;
                        HTREEITEM parents_item;
                        for (int z=0; z<m_product.size(); z++)
                        {
                            if(uint_p_serial_number == m_product.at(z).serial_number)
                            {
                                find_parents = true;
                                parents_item = m_product.at(z).product_item;
                                break;
                            }
                        }

                        if(find_parents)
                        {
                            CString strProdcut=bado.m_pRecordset->GetCollect("Product_name");
                            tvInsert.hParent = parents_item ; // 指定父句柄
                            tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
                            tvInsert.item.pszText =(LPTSTR)(LPCTSTR) strProdcut;
                            //TRACE(strProdcut);
                            tvInsert.hInsertAfter =TVI_SORT;// TVI_LAST; // 项目插入方式


                            int temp_product_class_id=bado.m_pRecordset->GetCollect("Product_class_ID");
                            if(temp_product_class_id==PM_NC)
                                TVINSERV_NET_WORK
                                else if(temp_product_class_id==LED_PRODUCT_MODEL)
                                    TVINSERV_LED
                                    else if(temp_product_class_id==PM_SOLAR)
                                        TVINSERV_SOLAR
                                        else if (temp_product_class_id == PM_CM5 ) //CM5
                                            TVINSERV_CMFIVE
                                            else if (temp_product_class_id == PM_T3PT10||
                                                     temp_product_class_id == PM_T3IOA||
                                                     temp_product_class_id == PM_T332AI||
                                                     temp_product_class_id ==  PM_T38AI16O||
                                                     temp_product_class_id == PM_T38I13O||
                                                     temp_product_class_id == PM_T34AO||
                                                     temp_product_class_id == PM_T36CT||
                                                     temp_product_class_id == PM_T322AI||
                                                     temp_product_class_id == PM_T38AI8AO6DO) //T3
                                                TVINSERV_NET_WORK
                                                else if (temp_product_class_id ==PM_MINIPANEL )//Mini Panel
                                                    TVINSERV_MINIPANEL
                                                    else if (temp_product_class_id == PM_AirQuality) //AirQuality
                                                        TVINSERV_TSTAT6
                                                        else if (temp_product_class_id == PM_LightingController)//Lightingcontroller
                                                            TVINSERV_LC          //tree0412
                                                            else if (temp_product_class_id == PM_TSTAT7)//TSTAT7 &TSTAT6 //tree0412
                                                                TVINSERV_LED //tree0412
                                                                else if(temp_product_class_id == PM_TSTAT6||temp_product_class_id == PM_TSTAT7||temp_product_class_id == PM_TSTAT5i||temp_product_class_id == PM_TSTAT8)
                                                                    TVINSERV_TSTAT6
                                                                    else if((temp_product_class_id == PM_CO2_NET) || (temp_product_class_id == PM_CO2_RS485)||(temp_product_class_id == PM_PRESSURE_SENSOR))
                                                                        TVINSERV_CO2
                                                                        else if (temp_product_class_id == PM_CS_SM_AC||temp_product_class_id == PM_CS_SM_DC||temp_product_class_id == PM_CS_RSM_AC||temp_product_class_id == PM_CS_RSM_DC)
                                                                        {
                                                                            TVINSERV_CS3000
                                                                        }
                                                                        else

                                                                            TVINSERV_TSTAT

                                                                            HTREEITEM hSubItem=m_pTreeViewCrl->InsertItem(&tvInsert);

                            HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hSubItem);
                            if (hParent != NULL)
                                m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);

                            tree_product m_product_temp;
                            m_product_temp.product_item  =hSubItem;

                            temp_variant=bado.m_pRecordset->GetCollect("Serial_ID");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");

                            long temp_serial_id = (long)(_wtoi64(strSql));
                            unsigned int correct_id = (DWORD)(_wtoi64(strSql));
                            //用于将以前数据库中的 负的序列号 修改为正的;Add by Fance
                            if(temp_serial_id < 0)
                            {
                                CString wrong_serial_id;
                                wrong_serial_id = strSql;
                                CString correct_serial_id;
                                CString str_temp;
                                correct_serial_id.Format(_T("%u"),correct_id);
                                try
                                {
                                    str_temp.Format(_T("update ALL_NODE set Serial_ID ='%s' where Serial_ID = '%s'"),correct_serial_id, wrong_serial_id);
                                    bado.m_pConnection->Execute(str_temp.GetString(),NULL,adCmdText);
                                }
                                catch(_com_error *e)
                                {
                                    AfxMessageBox(e->ErrorMessage());
                                }
                            }
                            m_product_temp.serial_number= correct_id;

                            temp_variant=bado.m_pRecordset->GetCollect("Product_ID");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.product_id=_wtoi(strSql);
                            temp_variant=bado.m_pRecordset->GetCollect("Custom");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.Custom=strSql;
                            temp_variant=bado.m_pRecordset->GetCollect("NetworkCard_Address");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.NetworkCard_Address=strSql;
                            temp_variant=bado.m_pRecordset->GetCollect("Product_class_ID");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.product_class_id=_wtoi(strSql);
                            temp_variant=bado.m_pRecordset->GetCollect("Hardware_Ver");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.hardware_version=(float)_wtof(strSql);

                            temp_variant=bado.m_pRecordset->GetCollect("Software_Ver");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.software_version=(float)_wtof(strSql);

                            temp_variant=bado.m_pRecordset->GetCollect("EPsize");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.nEPsize=(int)_wtol(strSql);

                            temp_variant=bado.m_pRecordset->GetCollect("Protocol");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            m_product_temp.protocol = (int)_wtoi(strSql);

                            temp_variant=bado.m_pRecordset->GetCollect("Bautrate");//
                            if(temp_variant.vt!=VT_NULL)
                                strSql=temp_variant;
                            else
                                strSql=_T("");
                            if(_wtoi(strSql) !=0)
                                m_product_temp.baudrate = _wtoi(strSql);
                            else
                                m_product_temp.baudrate = 19200;
                            if(m_product_temp.protocol == PROTOCOL_BACNET_IP)
                            {
                                char cTemp1[255];
                                memset(cTemp1,0,255);
                                WideCharToMultiByte( CP_ACP, 0, strSql.GetBuffer(), -1, cTemp1, 255, NULL, NULL );
                                DWORD dwIP = inet_addr(cTemp1);

                                m_product_temp.baudrate=dwIP;//_wtoi(strTemp);
                            }
                            else
                                m_product_temp.baudrate=_wtoi(strSql);
                            if (m_product_temp.product_class_id == PM_NC)
                            {
                                m_product_temp.baudrate = 19200;
                            }
                            ////
                            temp_variant=bado.m_pRecordset->GetCollect("Online_Status");//
                            if(temp_variant.vt!=VT_NULL)
                            {
                                m_product_temp.status = temp_variant;
                                m_product_temp.status_last_time[0] = m_product_temp.status;
                                m_product_temp.status_last_time[1] = false;
                                m_product_temp.status_last_time[2] = false;
                            }
                            else
                            {
                                m_product_temp.status = false;
                                m_product_temp.status_last_time[0] = false;
                                m_product_temp.status_last_time[1] = false;
                                m_product_temp.status_last_time[2] = false;
                            }

                            temp_variant=bado.m_pRecordset->GetCollect("Product_name");//
                            if(temp_variant.vt!=VT_NULL)
                            {
                                m_product_temp.NameShowOnTree = temp_variant;
                            }
                            else
                            {
                                m_product_temp.NameShowOnTree = _T("");

                            }


                            m_product_temp.BuildingInfo=m_subNetLst.at(m_nCurSubBuildingIndex);
                            //20120423
                            if(((strSql.CompareNoCase(_T("19200")) == 0)) || (strSql.CompareNoCase(_T("9600")) == 0) || ((strSql.CompareNoCase(_T("38400")) == 0)))
                            {
                                m_product_temp.BuildingInfo.strIp.Empty();
                                m_product_temp.BuildingInfo.strBaudRate = strSql;
                            }
                            else
                            {
                                m_product_temp.BuildingInfo.strIp = strSql;
                            }

                            temp_variant=bado.m_pRecordset->GetCollect("Com_Port");//
                            if(temp_variant.vt!=VT_NULL)
                            {
                                strSql=temp_variant;
                                m_product_temp.ncomport = _wtoi(strSql);
                            }
                            else
                            {
                                strSql=_T("");
                                m_product_temp.ncomport = 0;
                            }
                            m_product_temp.BuildingInfo.strIpPort = _T("10000");
                            temp_variant=bado.m_pRecordset->GetCollect("Background_imgID");
                            if(temp_variant.vt!=VT_NULL)
                                m_product_temp.strImgPathName=temp_variant;
                            else
                                m_product_temp.strImgPathName=_T("");

                            temp_variant=bado.m_pRecordset->GetCollect("Parent_SerialNum");
                            if(temp_variant.vt!=VT_NULL)
                            {
                                CString temp_value1;
                                temp_value1 = temp_variant;
                                m_product_temp.note_parent_serial_number=(unsigned int)_wtoi(temp_value1);
                            }
                            else
                                m_product_temp.note_parent_serial_number=0;

                            temp_variant=bado.m_pRecordset->GetCollect("Panal_Number");
                            if(temp_variant.vt!=VT_NULL)
                            {
                                CString temp_value1;
                                temp_value1 = temp_variant;
                                m_product_temp.panel_number=(unsigned char)_wtoi(temp_value1);
                            }
                            else
                                m_product_temp.panel_number=0;

                            temp_variant=bado.m_pRecordset->GetCollect("Object_Instance");
                            if(temp_variant.vt!=VT_NULL)
                            {
                                CString temp_value1;
                                temp_value1 = temp_variant;
                                m_product_temp.object_instance=(unsigned int)_wtoi(temp_value1);
                            }
                            else
                                m_product_temp.object_instance=0;

                            m_product.push_back(m_product_temp);

                        }
                        bado.m_pRecordset->MoveNext();
                    }
                }
                bado.CloseRecordset();
            }
        }
    }
    m_pTreeViewCrl->Expand(hTreeSubbuilding, TVE_EXPAND);
}
// scan Tstats in database
void CMainFrame::ScanTstatInDB(void)
{
    if(product_sort_way == SORT_BY_CONNECTION)
    {
        LoadProductFromDB();
        PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);
        return;
    }
    CADO ado;
    ado.OnInitADOConn();
    try
    {

        TRACE(_T("Scan TStat In DB!!  \n"));
#if 1
        ClearBuilding();
        m_product.clear();

// 	m_pCon.CreateInstance(_T("ADODB.Connection"));
// 	m_pRs.CreateInstance(_T("ADODB.Recordset"));
// 	m_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);
        CString strSql;
        //strSql.Format(_T("select * from Building where Main_BuildingName = '%s'"),m_strMainBuildingName);
        //strSql.Format(_T("select * from Building order by Main_BuildingName where Default_SubBuilding=-1"));
        strSql.Format(_T("select * from Building where Default_SubBuilding=-1"));
        //m_pRs->Open((_variant_t)strSql,_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);
        ado.m_pRecordset=ado.OpenRecordset(strSql);
        int count =ado.GetRecordCount(ado.m_pRecordset); //ado.m_pRecordset->GetRecordCount();
        _variant_t temp_variant;
        if(count<=0)
        {
            /*if(m_pRs->State)
            m_pRs->Close();
            if(m_pCon->State)
            m_pCon->Close();*/
            //	PostMessage(ID_NODEFAULTMAINBUILDING_MSG,0,0);
            ado.CloseRecordset();
            ado.CloseConn();
            AfxMessageBox(_T("There is no default building, please select a building Firstly!"));

            return;
        }

        m_strCurMainBuildingName=ado.m_pRecordset->GetCollect("Main_BuildingName");

        CString cs_temp_protocol;
        CString cs_temp_baudrate;
        temp_variant=ado.m_pRecordset->GetCollect("Protocal");//
        if(temp_variant.vt!=VT_NULL)
            cs_temp_protocol=temp_variant;
        else
        {
            cs_temp_protocol=_T("Auto");
            strSql.Format(_T("update Building set Protocal='Auto' where Main_BuildingName ='%s'"), m_strCurMainBuildingName);
            ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
        }

        if(cs_temp_protocol.CompareNoCase(_T("Modbus 485")) == 0 )
        {
            current_building_protocol = P_MODBUS_485;
        }
        else if(cs_temp_protocol.CompareNoCase(_T("Modbus TCP")) == 0 )
        {
            current_building_protocol = P_MODBUS_TCP;
        }
        else if(cs_temp_protocol.CompareNoCase(_T("Bacnet MSTP")) == 0 )
        {
            current_building_protocol = P_BACNET_MSTP;
        }
        else if(cs_temp_protocol.CompareNoCase(_T("Remote Device")) == 0 )
        {
            current_building_protocol = P_REMOTE_DEVICE;
        }
        else
        {
            current_building_protocol = P_AUTO;
        }


        CString StrComport;
        CString StrBaudrate;


        CString StrIp;
        if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP))
        {


            temp_variant=ado.m_pRecordset->GetCollect("Braudrate");//
            if(temp_variant.vt!=VT_NULL)
            {
                cs_temp_baudrate = temp_variant;
            }
            else
            {
                cs_temp_protocol=_T("19200");
                strSql.Format(_T("update Building set Braudrate='19200' where Main_BuildingName ='%s'"), m_strCurMainBuildingName);
                ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
            }

            current_building_baudrate = _wtoi(cs_temp_baudrate);
            if((current_building_baudrate!= 19200) && (current_building_baudrate != 9600) && (current_building_baudrate != 38400))
            {
                current_building_baudrate = 19200;
            }

            //current_building_comport
            temp_variant = ado.m_pRecordset->GetCollect(_T("Com_Port"));
            if(temp_variant.vt!=VT_NULL)
            {
                StrComport=temp_variant;
                current_building_comport = _wtoi(StrComport.Mid(3));
            }
            else
            {
                current_building_comport=-1;
            }

        }
        if (current_building_protocol == P_MODBUS_TCP || current_building_protocol == P_BACNET_IP || current_building_protocol == P_REMOTE_DEVICE)
        {
            temp_variant=ado.m_pRecordset->GetCollect("Ip_Address");//
            if(temp_variant.vt!=VT_NULL)
            {
                StrIp = temp_variant;
                m_str_curBuilding_Domain_IP = StrIp;
            }
            else
            {
                m_str_curBuilding_Domain_IP.Empty();
            }

        }
        else
            m_str_curBuilding_Domain_IP.Empty();
        /*if(m_pRs->State)
        	m_pRs->Close();*/
        ado.CloseRecordset();
        m_subNetLst.clear();


        strSql.Format(_T("select * from Building where Main_BuildingName ='%s'"),m_strCurMainBuildingName);
        //m_pRs->Open(_variant_t(strSql),_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);
        ado.m_pRecordset=ado.OpenRecordset(strSql);
        m_nCurSubBuildingIndex=-1;
        int nTemp=-1;
        while(VARIANT_FALSE==ado.m_pRecordset->EndOfFile)
        {
            nTemp++;
            int nDefault=0;
            Building_info temBuildingInfo;
            //memset(&temBuildingInfo,0,sizeof(temBuildingInfo));
            temp_variant=ado.m_pRecordset->GetCollect("Building_Name");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strBuildingName=temp_variant;
            else
                temBuildingInfo.strBuildingName=_T("");



            temp_variant=ado.m_pRecordset->GetCollect("Protocal");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strProtocol=temp_variant;
            else
                temBuildingInfo.strProtocol=_T("");

            temp_variant=ado.m_pRecordset->GetCollect("Ip_Address");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strIp=temp_variant;
            else
                temBuildingInfo.strIp=_T("");


            temp_variant=ado.m_pRecordset->GetCollect("Com_Port");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strComPort=temp_variant;
            else
                temBuildingInfo.strComPort=_T("");


            temp_variant=ado.m_pRecordset->GetCollect("Ip_Port");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strIpPort=temp_variant;
            else
                temBuildingInfo.strIpPort=_T("");




            temBuildingInfo.hCommunication=NULL;

            temp_variant=ado.m_pRecordset->GetCollect("Main_BuildingName");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strMainBuildingname=temp_variant;
            else
                temBuildingInfo.strMainBuildingname=temp_variant;



            temp_variant=ado.m_pRecordset->GetCollect("Braudrate");//
            if(temp_variant.vt!=VT_NULL)
                temBuildingInfo.strBaudRate=temp_variant;
            else
                temBuildingInfo.strBaudRate=_T("");


            CString Building_DBpath;
            nDefault=ado.m_pRecordset->GetCollect("Default_SubBuilding");
            if(nDefault==-1)
            {
                m_nCurSubBuildingIndex=nTemp;
            }
            Building_DBpath=ado.m_pRecordset->GetCollect("Building_Path");

            int index= Building_DBpath.Find(_T("Database"));
            Building_DBpath.Delete(0,index);

            g_strCurBuildingDatabasefilePath=GetExePath(true)+  Building_DBpath;
            ado.m_pRecordset->MoveNext();
            m_subNetLst.push_back(temBuildingInfo);
        }
        if(m_subNetLst.size()<=0)
            AfxMessageBox(_T("There is no default building,please select a building First！"));

        ado.CloseRecordset();


        TV_INSERTSTRUCT tvInsert;////added

        m_strCurSubBuldingName=m_subNetLst.at(m_nCurSubBuildingIndex).strBuildingName;


//	for(int k=0;k<m_subNetLst.size();k++)
        {
            CString strBuilding=m_strCurSubBuldingName;//m_subNetLst.at(k).strBuildingName;

            tvInsert.hParent = TVI_ROOT; // 指定父句柄
            tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
            tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strBuilding;
            tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
            TVINSERV_BUILDING
            HTREEITEM hTreeSubbuilding=NULL;
            //hTreeSubbuilding=m_pTreeViewCrl->InsertItem(&tvInsert);//插入subbuilding。
            hTreeSubbuilding=m_pTreeViewCrl->InsertSubnetItem(&tvInsert);//插入subbuilding。
            // m_pTreeViewCrl->Expand(hTreeSubbuilding,TVE_EXPAND);//Add

            // Expand the parent, if possible.
            HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hTreeSubbuilding);
            if (hParent != NULL)
                m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);


            if (hTreeSubbuilding!=NULL)
            {
                //	m_subNetLst.at(k).hbuilding_item=hTreeSubbuilding;
            }
            CBADO bado;
            bado.SetDBPath(g_strCurBuildingDatabasefilePath);
            bado.OnInitADOConn();
            //	m_pRs->Close();
            ////begin floor nodes///////////////////////////////////////////////////////////////

            if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP))
            {
                strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s' and Com_Port = '%d' and Protocol = '%d'"),strBuilding,current_building_comport,current_building_protocol);
            }
            else if(current_building_protocol == P_MODBUS_TCP || current_building_protocol == P_BACNET_IP)
            {
                strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s' and Bautrate = '%s' and Protocol = '%d'"),strBuilding,StrIp,current_building_protocol);
            }
            else if(current_building_protocol == P_REMOTE_DEVICE)
            {
                strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s' and Bautrate = '%s' and Protocol = '%d'"),strBuilding,StrIp,current_building_protocol);
            }
            else
            {
                strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s'"),strBuilding);
            }

            //HRESULT hR=bado.m_pRecordset->Open(_variant_t(strSql),_variant_t((IDispatch *),true),adOpenStatic,adLockOptimistic,adCmdText);
            bado.m_pRecordset=bado.OpenRecordset(strSql);
            //int nTemp2 = m_pRs->RecordCount;
            int nTemp2 = bado.m_pRecordset->RecordCount;
            vector <tree_floor> tmpfloorLst;//
            tmpfloorLst.empty();
            while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)//所有楼层。
            {
                CString strFloorName= bado.m_pRecordset->GetCollect("Floor_name");
                ///*********tree***********************************
                tvInsert.hParent = hTreeSubbuilding; // 指定父句柄
                tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象

                tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strFloorName;
                tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
                TVINSERV_FLOOR

                HTREEITEM hTreeFloor=NULL;
                //hTreeFloor=m_pTreeViewCrl->InsertItem(&tvInsert);//返回楼层的句柄
                hTreeFloor=m_pTreeViewCrl->InsertFloorItem(&tvInsert);//返回楼层的句柄

                HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hTreeFloor);
                if (hParent != NULL)
                    m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);


                tree_floor m_floor_temp;
                m_floor_temp.building_item=hTreeSubbuilding;
                m_floor_temp.floor_item =hTreeFloor;
                m_floor_temp.strFloorName=strFloorName;
                m_floorLst.push_back(m_floor_temp);
                tmpfloorLst.push_back(m_floor_temp);

                bado.m_pRecordset->MoveNext();
            }


            /*if(m_pRs->State)
            m_pRs->Close(); */
            bado.CloseRecordset();
            vector <tree_room> tmproomLst;
            ////end floor nodes/////////////////////////////////////////////////////////////////
            ///begin room nodes///////////////////////////////////////////////////////////////////////
            for(unsigned int i=0; i<tmpfloorLst.size(); i++)
            {
                //loop for Room Name f
                //	m_pRs->Close();
                CString strFloorName;
                strFloorName=tmpfloorLst.at(i).strFloorName;
                CString temp_str;

                //temp_str.Format(_T("select DISTINCT Room_name from ALL_NODE where Building_Name = '"+strBuilding+"' and Floor_name='"+strFloorName+"'"));
                //m_pRs->Open(_variant_t(temp_str),_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);

                if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP))
                {
                    //strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s' and Com_Port = '%s' and Protocol = '%s'"),strBuilding,StrComport,current_building_protocol);
                    //	temp_str.Format(_T("select DISTINCT Room_name from ALL_NODE where Building_Name = '"+strBuilding+"' and Floor_name='"+strFloorName+"'"));
                    temp_str.Format(_T("select DISTINCT Room_name from ALL_NODE where Building_Name = '%s' and Floor_name='%s' and Com_Port = '%d' and Protocol = '%d'"),strBuilding,strFloorName,current_building_comport,current_building_protocol);
                }
                else if(current_building_protocol == P_MODBUS_TCP || current_building_protocol == P_BACNET_IP || current_building_protocol == P_REMOTE_DEVICE)
                {
                    //strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s' and Bautrate = '%s' and Protocol = '%s'"),strBuilding,StrIp,current_building_protocol);
                    temp_str.Format(_T("select DISTINCT Room_name from ALL_NODE where Building_Name = '%s' and Floor_name='%s' and Bautrate = '%s' and Protocol = '%d'"),strBuilding,strFloorName,StrIp,current_building_protocol);
                }
                else
                {
                    //strSql.Format(_T("select DISTINCT Floor_name from ALL_NODE where Building_Name = '%s'"),strBuilding);
                    temp_str.Format(_T("select DISTINCT Room_name from ALL_NODE where Building_Name = '"+strBuilding+"' and Floor_name='"+strFloorName+"'"));
                }

                bado.m_pRecordset=bado.OpenRecordset(temp_str);
                //插入每个房间到相关的楼层。
                while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)
                {
                    CString strRoomName;
                    strRoomName=bado.m_pRecordset->GetCollect("Room_name");
                    tvInsert.hParent = tmpfloorLst.at(i).floor_item ; // 指定父句柄
                    tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
                    tvInsert.item.pszText = (LPTSTR)(LPCTSTR)strRoomName;
                    tvInsert.hInsertAfter = TVI_LAST; // 项目插入方式
                    TVINSERV_ROOM
                    HTREEITEM hTreeRoom=NULL;
                    //hTreeRoom=m_pTreeViewCrl->InsertItem(&tvInsert);
                    hTreeRoom=m_pTreeViewCrl->InsertRoomItem(&tvInsert);
                    HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hTreeRoom);
                    if (hParent != NULL)
                        m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);

                    tree_room m_room_temp;

                    m_room_temp.building_item=m_floorLst.at(i).building_item ;
                    m_room_temp.floor_item =m_floorLst.at(i).floor_item ;
                    m_room_temp.room_item =hTreeRoom;
                    m_room_temp.strFloorName=strFloorName;
                    m_room_temp.strRoomName=strRoomName;
                    m_roomLst.push_back(m_room_temp);
                    tmproomLst.push_back(m_room_temp);
                    bado.m_pRecordset->MoveNext();
                }
                /* if(m_pRs->State)
                m_pRs->Close(); */
                bado.CloseRecordset();
            }
            ///////end room nodes//////////////////////////////////////////////////////////////////////
            //////Begin product node/////////////////////////////////////////////////////////////////
            ///每个房间；
            for(UINT i=0; i<tmproomLst.size(); i++)
            {
                //loop for product Name
                //m_pRs->Close();
                CString str_temp;
                CString StrFloorName;
                CString strRoomName;
                strRoomName=tmproomLst.at(i).strRoomName;
                StrFloorName=tmproomLst.at(i).strFloorName;



                if((current_building_protocol == P_MODBUS_485) || (current_building_protocol == P_BACNET_MSTP))
                {
                    //str_temp.Format(_T("select * from ALL_NODE where Floor_name = '"+StrFloorName+"' and\
                    //	  Room_name = '"+strRoomName+"'and Building_Name = '"+strBuilding+"'  ORDER BY Product_ID ASC "));
                    str_temp.Format(_T("select * from ALL_NODE where Floor_name = '%s' and  Room_name = '%s' and Building_Name = '%s' and Com_Port = '%d' and Protocol = '%d'  ORDER BY Product_ID ASC"),StrFloorName,strRoomName,strBuilding,current_building_comport,current_building_protocol);
                }
                else if (current_building_protocol == P_MODBUS_TCP || current_building_protocol == P_BACNET_IP || current_building_protocol == P_REMOTE_DEVICE)
                {
                    str_temp.Format(_T("select * from ALL_NODE where Floor_name = '%s' and  Room_name = '%s' and Building_Name = '%s' and Bautrate = '%s' and Protocol = '%d'  ORDER BY Product_ID ASC"),StrFloorName,strRoomName,strBuilding,StrIp,current_building_protocol);
                }
                else
                {
                    str_temp.Format(_T("select * from ALL_NODE where Floor_name = '"+StrFloorName+"' and\
																							  Room_name = '"+strRoomName+"'and Building_Name = '"+strBuilding+"'  ORDER BY Product_ID ASC "));
                }

                //m_pRs->Open(_variant_t(str_temp),_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);
                //插入每个产品到相关的房间。
                bado.m_pRecordset=bado.OpenRecordset(str_temp);
                int count = bado.GetRecordCount(bado.m_pRecordset);
                while(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)
                {
                    CString strProdcut=bado.m_pRecordset->GetCollect("Product_name");
                    tvInsert.hParent = tmproomLst.at(i).room_item ; // 指定父句柄
                    tvInsert.item.mask = ITEM_MASK; // 指定TV_ITEM结构对象
                    tvInsert.item.pszText =(LPTSTR)(LPCTSTR) strProdcut;
                    //TRACE(strProdcut);
                    tvInsert.hInsertAfter =TVI_SORT;// TVI_LAST; // 项目插入方式
                    int temp_product_class_id=bado.m_pRecordset->GetCollect("Product_class_ID");

                    /*
                    int const PM_T3PT10= 26;
                    int const PM_T3IOA = 21;
                    int const PM_T332AI = 22;
                    int const PM_T38AI16O = 23;
                    int const PM_T38I13O = 20;
                    int const PM_T34AO = 28;
                    int const PM_T36CT = 29;
                    */
#if 1
                    if(temp_product_class_id==PM_NC)
                        TVINSERV_NET_WORK
                        else if(temp_product_class_id==LED_PRODUCT_MODEL)
                            TVINSERV_LED
                            else if(temp_product_class_id==PM_SOLAR)
                                TVINSERV_SOLAR
                                else if (temp_product_class_id == PM_CM5 ) //CM5
                                    TVINSERV_CMFIVE
                                    else if (temp_product_class_id == PM_T3PT10||
                                             temp_product_class_id == PM_T3IOA||
                                             temp_product_class_id == PM_T332AI||
                                             temp_product_class_id ==  PM_T38AI16O||
                                             temp_product_class_id == PM_T38I13O||
                                             temp_product_class_id == PM_T34AO||
                                             temp_product_class_id == PM_T36CT||
                                             temp_product_class_id == PM_T322AI||
                                             temp_product_class_id == PM_T38AI8AO6DO) //T3
                                        TVINSERV_NET_WORK
                                        //else if (temp_product_class_id ==PM_T3IOA )//T3-8AI8AO
                                        //	TVINSERV_NET_WORK
                                        else if (temp_product_class_id ==PM_MINIPANEL )//Mini Panel
                                            TVINSERV_MINIPANEL
                                            else if (temp_product_class_id == PM_AirQuality) //AirQuality
                                                TVINSERV_TSTAT6
                                                else if (temp_product_class_id == PM_LightingController)//Lightingcontroller
                                                    //TVINSERV_NET_WORK  //tree0412
                                                    TVINSERV_LC          //tree0412
                                                    else if (temp_product_class_id == PM_TSTAT7)//TSTAT7 &TSTAT6 //tree0412
                                                        TVINSERV_LED //tree0412
                                                        else if(temp_product_class_id == PM_TSTAT6||temp_product_class_id == PM_TSTAT7||temp_product_class_id == PM_TSTAT5i||temp_product_class_id == PM_TSTAT8)
                                                            TVINSERV_TSTAT6
                                                            else if((temp_product_class_id == PM_CO2_NET) || (temp_product_class_id == PM_CO2_RS485)||(temp_product_class_id == PM_PRESSURE_SENSOR))
                                                                TVINSERV_CO2
// 					PM_CS_SM_AC
// 					PM_CS_SM_DC
// 					PM_CS_RSM_AC
// 					PM_CS_RSM_DC
                                                                else if (temp_product_class_id == PM_CS_SM_AC||temp_product_class_id == PM_CS_SM_DC||temp_product_class_id == PM_CS_RSM_AC||temp_product_class_id == PM_CS_RSM_DC)
                                                                {
                                                                    TVINSERV_CS3000
                                                                }
                                                                else

                                                                    TVINSERV_TSTAT
#endif



                                                                    //	pBuildingInfo->hbuilding_item=

                                                                    //HTREEITEM hTreeRoom=m_pTreeViewCrl->InsertItem(&tvInsert);
                                                                    HTREEITEM hTreeRoom=m_pTreeViewCrl->InsertDeviceItem(&tvInsert);

                    HTREEITEM hParent = m_pTreeViewCrl->GetParentItem(hTreeRoom);
                    if (hParent != NULL)
                        m_pTreeViewCrl->Expand(hParent, TVE_EXPAND);


                    tree_product m_product_temp;
                    m_product_temp.product_item  =hTreeRoom;

                    //m_product_temp.serial_number = m_pRs->GetCollect("Serial_ID");
                    temp_variant=bado.m_pRecordset->GetCollect("Serial_ID");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");


                    long temp_serial_id = (long)(_wtoi64(strSql));
                    unsigned int correct_id = (DWORD)(_wtoi64(strSql));

                    //long temp_serial_id = _wtol(strSql);
                    //unsigned int correct_id = (DWORD)(_wtol(strSql));
                    //用于将以前数据库中的 负的序列号 修改为正的;Add by Fance
                    if(temp_serial_id < 0)
                    {
                        CString wrong_serial_id;
                        wrong_serial_id = strSql;
                        CString correct_serial_id;
                        correct_serial_id.Format(_T("%u"),correct_id);
                        try
                        {
                            str_temp.Format(_T("update ALL_NODE set Serial_ID ='%s' where Serial_ID = '%s'"),correct_serial_id, wrong_serial_id);
                            bado.m_pConnection->Execute(str_temp.GetString(),NULL,adCmdText);
                        }
                        catch(_com_error *e)
                        {
                            AfxMessageBox(e->ErrorMessage());
                        }
                    }
                    m_product_temp.serial_number= correct_id;

                    //m_product_temp.product_id =m_pRs->GetCollect("Product_ID");
                    temp_variant=bado.m_pRecordset->GetCollect("Product_ID");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.product_id=_wtoi(strSql);

                    temp_variant=bado.m_pRecordset->GetCollect("NetworkCard_Address");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.NetworkCard_Address=strSql;
                    //	m_product_temp.product_class_id = m_pRs->GetCollect("Product_class_ID");
                    temp_variant=bado.m_pRecordset->GetCollect("Product_class_ID");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.product_class_id=_wtoi(strSql);

                    //	m_product_temp.hardware_version= m_pRs->GetCollect("Hardware_Ver");
                    temp_variant=bado.m_pRecordset->GetCollect("Hardware_Ver");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.hardware_version=(float)_wtof(strSql);

                    //
                    temp_variant=bado.m_pRecordset->GetCollect("Software_Ver");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.software_version=(float)_wtof(strSql);

                    //
                    temp_variant=bado.m_pRecordset->GetCollect("EPsize");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.nEPsize=(int)_wtol(strSql);

                    //m_product_temp.baudrate=m_pRs->GetCollect("Bautrate");
                    temp_variant=bado.m_pRecordset->GetCollect("Protocol");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    m_product_temp.protocol = (int)_wtoi(strSql);

                    temp_variant=bado.m_pRecordset->GetCollect("Bautrate");//
                    if(temp_variant.vt!=VT_NULL)
                        strSql=temp_variant;
                    else
                        strSql=_T("");
                    if(_wtoi(strSql) !=0)
                        m_product_temp.baudrate = _wtoi(strSql);
                    else
                        m_product_temp.baudrate = 19200;
                    if(m_product_temp.protocol == PROTOCOL_BACNET_IP)
                    {
                        char cTemp1[255];
                        memset(cTemp1,0,255);
                        WideCharToMultiByte( CP_ACP, 0, strSql.GetBuffer(), -1, cTemp1, 255, NULL, NULL );
                        DWORD dwIP = inet_addr(cTemp1);

                        m_product_temp.baudrate=dwIP;//_wtoi(strTemp);
                    }
                    else
                        m_product_temp.baudrate=_wtoi(strSql);
                    if (m_product_temp.product_class_id == PM_NC)
                    {
                        m_product_temp.baudrate = 19200;
                    }
                    ////
                    temp_variant=bado.m_pRecordset->GetCollect("Online_Status");//
                    if(temp_variant.vt!=VT_NULL)
                    {
                        m_product_temp.status = temp_variant;
                        m_product_temp.status_last_time[0] = m_product_temp.status;
                        m_product_temp.status_last_time[1] = false;
                        m_product_temp.status_last_time[2] = false;
                    }
                    else
                    {
                        m_product_temp.status = false;
                        m_product_temp.status_last_time[0] = false;
                        m_product_temp.status_last_time[1] = false;
                        m_product_temp.status_last_time[2] = false;
                    }

                    temp_variant=bado.m_pRecordset->GetCollect("Product_name");//
                    if(temp_variant.vt!=VT_NULL)
                    {
                        m_product_temp.NameShowOnTree = temp_variant;
                    }
                    else
                    {
                        m_product_temp.NameShowOnTree = _T("");

                    }


                    m_product_temp.BuildingInfo=m_subNetLst.at(m_nCurSubBuildingIndex);
//20120423
                    if(((strSql.CompareNoCase(_T("19200")) == 0)) || (strSql.CompareNoCase(_T("9600")) == 0) || ((strSql.CompareNoCase(_T("38400")) == 0)))
                    {
                        m_product_temp.BuildingInfo.strIp.Empty();
                        m_product_temp.BuildingInfo.strBaudRate = strSql;
                    }
                    else
                    {
                        m_product_temp.BuildingInfo.strIp = strSql;
                    }

#if 0
                    m_product_temp.BuildingInfo.strIp = strSql;
#endif
                    temp_variant=bado.m_pRecordset->GetCollect("Com_Port");//
                    if(temp_variant.vt!=VT_NULL)
                    {
                        strSql=temp_variant;
                        m_product_temp.ncomport = _wtoi(strSql);
                    }
                    else
                    {
                        strSql=_T("");
                        m_product_temp.ncomport = 0;
                    }

                    //m_product_temp.BuildingInfo.strIpPort=strSql;
                    m_product_temp.BuildingInfo.strIpPort = _T("10000");


                    temp_variant=bado.m_pRecordset->GetCollect("Background_imgID");
                    if(temp_variant.vt!=VT_NULL)
                        m_product_temp.strImgPathName=temp_variant;
                    else
                        m_product_temp.strImgPathName=_T("");

                    temp_variant=bado.m_pRecordset->GetCollect("Custom");
                    if(temp_variant.vt!=VT_NULL)
                        m_product_temp.Custom=temp_variant;
                    else
                        m_product_temp.Custom=_T("");

                    if (g_selected_serialnumber == m_product_temp.serial_number)
                    {
                        m_lasttime_tree_node  =  m_product_temp;
                        m_pTreeViewCrl->SetSelectItem(m_product_temp.product_item);//在线的时候才将颜色变红;
                        m_pTreeViewCrl->SetSelectSerialNumber(m_product_temp.serial_number);
                        m_current_tree_node =   m_product_temp;
                        /*g_selected_serialnumber = m_product.at(i).serial_number;*/
                    }

                    temp_variant=bado.m_pRecordset->GetCollect("Parent_SerialNum");
                    if(temp_variant.vt!=VT_NULL)
                    {
                        CString temp_value1;
                        temp_value1 = temp_variant;
                        m_product_temp.note_parent_serial_number=(unsigned int)_wtoi(temp_value1);
                    }
                    else
                        m_product_temp.note_parent_serial_number=0;

                    temp_variant=bado.m_pRecordset->GetCollect("Panal_Number");
                    if(temp_variant.vt!=VT_NULL)
                    {
                        CString temp_value1;
                        temp_value1 = temp_variant;
                        m_product_temp.panel_number=(unsigned char)_wtoi(temp_value1);
                    }
                    else
                        m_product_temp.panel_number=0;

                    temp_variant=bado.m_pRecordset->GetCollect("Object_Instance");
                    if(temp_variant.vt!=VT_NULL)
                    {
                        CString temp_value1;
                        temp_value1 = temp_variant;
                        m_product_temp.object_instance=(unsigned int)_wtoi(temp_value1);
                    }
                    else
                        m_product_temp.object_instance=0;

                    m_product.push_back(m_product_temp);
                    bado.m_pRecordset->MoveNext();
                }

                /*	if(m_pRs->State)
                	m_pRs->Close(); */
                bado.CloseRecordset();

            }


            bado.CloseConn();
        }

        /*if(m_pRs->State)
        m_pRs->Close();
        if(m_pCon->State)
        m_pCon->Close();*/
        ado.CloseConn();
#endif



        PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);

        if(m_nCurSubBuildingIndex>=0)
        {
            m_strCurSubBuldingName=m_subNetLst.at(m_nCurSubBuildingIndex).strBuildingName;
            //	ConnectSubBuilding(m_subNetLst.at(m_nCurSubBuildingIndex));
        }

    }
    catch (...)
    {

    }
}

void CMainFrame::OnFileOpen()
{
    // TODO: Add your command handler code here
    AfxMessageBox(_T("Open configuration file."));
}
void CMainFrame::OnLoadConfigFile()
{
    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        MainFram_hwd = this->m_hWnd;
        //LoadBacnetConfigFile();
        LoadBacnetConfigFile(true,NULL);
        return;
    }
    //AfxMessageBox(_T("Load configuration file."));
    if(g_LoadConfigLevel==1)
    {
        CAfxMessageDialog dlg;
        CString strPromption;
        strPromption.LoadString(IDS_STRNOPRIVILEGE2);
        dlg.SetPromtionTxt(strPromption);
        dlg.DoModal();
        return;
    }

    int nCurID=g_tstat_id;
    g_bPauseMultiRead=TRUE;
// 	CGridLoad Dlg;
// 	Dlg.DoModal();
    g_tstat_id=nCurID;
    ReFresh();
    g_bPauseMultiRead=FALSE;
}

#include "Flash_Multy.h"
void CMainFrame::OnBatchFlashHex()
{

    b_pause_refresh_tree = true;
    bool temp_status = g_bPauseMultiRead;
    g_bPauseMultiRead = true;
    int temp_type = GetCommunicationType();


    BOOL bDontLinger = FALSE;
    setsockopt( h_Broad, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
    closesocket(h_Broad);

    SetCommunicationType(0);//关闭串口，供ISP 使用;
    close_com();



    CFlash_Multy dlg;
    dlg.DoModal();

    if(temp_type == 0)
    {
        int comport = GetLastOpenedComport();
        open_com(comport);
    }
    else
    {

    }
    SetCommunicationType(temp_type);

    //Fance Add. 在ISP 用完1234 4321 的端口之后，T3000 在重新打开使用，刷新listview 的网络设备要使用;
    h_Broad=::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    BOOL bBroadcast=TRUE;
    ::setsockopt(h_Broad,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));
    int iMode=1;
    ioctlsocket(h_Broad,FIONBIO, (u_long FAR*) &iMode);

    //SOCKADDR_IN bcast;
    h_bcast.sin_family=AF_INET;
    //bcast.sin_addr.s_addr=nBroadCastIP;
    h_bcast.sin_addr.s_addr=INADDR_BROADCAST;
    h_bcast.sin_port=htons(UDP_BROADCAST_PORT);

    //SOCKADDR_IN siBind;
    h_siBind.sin_family=AF_INET;
    h_siBind.sin_addr.s_addr=INADDR_ANY;
    h_siBind.sin_port=htons(RECV_RESPONSE_PORT);
    ::bind(h_Broad, (sockaddr*)&h_siBind,sizeof(h_siBind));
    b_pause_refresh_tree = false;
    g_bPauseMultiRead = temp_status;

    return;

}

void CMainFrame::OnConnect()
{


    //	return;
    if(m_strCurMainBuildingName.IsEmpty())
        return;
    if(m_nCurSubBuildingIndex==-1)
        return;
    if(m_subNetLst.size()<=0)
        return;

    Building_info build_info;
    //for(int i=0;i<m_subNetLst.size();i++)
    {
        build_info=m_subNetLst.at(m_nCurSubBuildingIndex);
        if (build_info.strProtocol.CompareNoCase(_T("Modbus TCP"))==0)
        {
            UINT n1,n2,n3,n4;
            if (ValidAddress(build_info.strIp,n1,n2,n3,n4)==FALSE)
            {
                //AfxMessageBox(_T("Invalidate IP Address!!"));
                //goto here;
                CString strInfo;
                strInfo.Format(_T("Invalidate IP Address,You can click config button to reset it."));
                SetPaneString(1, strInfo);
            }
            else
            {
                CString strPort;
                m_nIpPort=_wtoi(build_info.strIpPort);
                m_strIP=build_info.strIp;
                g_CommunicationType=1;
                SetCommunicationType(g_CommunicationType);
                if(Open_Socket2(build_info.strIp,m_nIpPort))
                {
                    CString strInfo;
                    strInfo.Format((_T("Open IP:%s successful.")),build_info.strIp);//prompt info;
                    SetPaneString(1,strInfo);
                    //connectionSuccessful = 1;
                    m_nStyle=1;
                    CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                    CFileFind fFind;
                    if(!fFind.FindFile(g_configfile_path))
                    {
                        /*WritePrivateProfileStringW(_T("Setting"),_T("Connection Type"),_T("0"),g_configfile_path);

                        WritePrivateProfileStringW(_T("Setting"),_T("COM Port"),_T("COM1"),g_configfile_path);
                        WritePrivateProfileStringW(_T("Setting"),_T("COM_Port"),_T("1"),g_configfile_path);
                        WritePrivateProfileStringW(_T("Setting"),_T("Baudrate"),_T("19200"),g_configfile_path);*/

                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("1"),g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),build_info.strIp,g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),build_info.strIpPort,g_configfile_path);

                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                    }
                    else
                    {
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("1"),g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),build_info.strIp,g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),build_info.strIpPort,g_configfile_path);

                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                    }



                    Invalidate();
                    //close_com();
                }
                else
                {
                    CString strInfo;
                    strInfo.Format((_T("Open IP:%s failed.")),build_info.strIp);//prompt info;
                    SetPaneString(1,strInfo);
                    //connectionSuccessful = 0;
                }

            }
        }

        if (build_info.strProtocol.CompareNoCase(_T("Modbus 485"))==0)
        {
            //rs485
            g_CommunicationType=0;
            SetCommunicationType(g_CommunicationType);
            CString strInfo;

            if (build_info.strComPort.GetLength()!=0)
            {
                int nComPort = _wtoi(build_info.strComPort.Mid(3));
                open_com(nComPort);//open*************************************
                CString strInfo;
                if(!is_connect())
                {
                    //strInfo=_T("Open ")+build_info.strComPort+_T(" Failure!");
                    //strInfo.Format(_T("COM: %d Connected: No"), nComPort);
                    strInfo.Format(_T("COM %d : Not available "), nComPort);
                    //connectionSuccessful = 0;
                    //SetPaneCommunicationPrompt(strInfo);
                    SetPaneString(1, strInfo);
                }
                else
                {
                    //strInfo=_T("Open ")+build_info.strComPort+_T(" Sucessful!");
                    strInfo.Format(_T("COM %d Connected: Yes"), nComPort);
                    //connectionSuccessful = 1;
                    //SetPaneCommunicationPrompt(strInfo);
                    SetPaneString(1, strInfo);
                    Change_BaudRate(default_com1_port_baudrate);
                    m_nStyle=1;
                    CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                    CFileFind fFind;
                    if(!fFind.FindFile(g_configfile_path))
                    {
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("0"),g_configfile_path);
                        strInfo.Format(_T("COM%d"),nComPort);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
                        strInfo.Format(_T("%d"),nComPort);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);
                        strInfo.Format(_T("%d"),default_com1_port_baudrate);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);


                        /*	WritePrivateProfileStringW(_T("Setting"),_T("IP Address"),build_info.strIp,g_configfile_path);
                        	WritePrivateProfileStringW(_T("Setting"),_T("IP Port"),build_info.strIpPort,g_configfile_path);

                        	WritePrivateProfileStringW(_T("Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                        	WritePrivateProfileStringW(_T("Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                        	WritePrivateProfileStringW(_T("Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);*/
                    }
                    else
                    {
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("0"),g_configfile_path);
                        strInfo.Format(_T("COM%d"),nComPort);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
                        strInfo.Format(_T("%d"),nComPort);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);
                        strInfo.Format(_T("%d"),default_com1_port_baudrate);
                        WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);
                    }

                    Invalidate();
                    //close_com();
                }
            }
        }//endof rs485 checking
    }


    //EnableMyToolBarButton(0, ID_CONNECT2, FALSE);
    //EnableMyToolBarButton(1, ID_DISCONNECT2, TRUE);
}
void CMainFrame::OnDisconnect()
{
    //AfxMessageBox(_T("DisConnect."));
    close_com();
    m_nStyle=2;
    Invalidate();
    CString strInfo = _T("No Connnection");
    //connectionSuccessful = 0;
    SetPaneString(1,strInfo);
    //strInfo = _T("Offline!");
    //SetPaneString(2,strInfo);


    //EnableMyToolBarButton(1, ID_DISCONNECT2, FALSE);
    //EnableMyToolBarButton(0, ID_CONNECT2, TRUE);

}

BOOL CMainFrame::ConnectDevice(LPCTSTR ip_address,int nport)
{
    CString connect_ip;
    if(m_hCurCommunication!=NULL)
    {
        CloseHandle(m_hCurCommunication);
        m_hCurCommunication=NULL;
    }

    CString strPort;
    m_nIpPort=nport;

    connect_ip=ip_address;

    g_CommunicationType=1;
    SetCommunicationType(g_CommunicationType);
    bool b=Open_Socket2(connect_ip,m_nIpPort);
    CString strInfo;
    //	strInfo.Format((_T("Open IP:%s successful")),build_info.str3Ip);//prompt info;
    //	SetPaneString(1,strInfo);
    if(b)
    {
        strInfo.Format((_T("Open IP:%s successful")),connect_ip);//prompt info;
        SetPaneString(1,strInfo);
        return TRUE;
    }
    else
    {
        strInfo.Format((_T("Open IP:%s failure")),connect_ip);//prompt info;
        SetPaneString(1,strInfo);
        //ValidOpenFailure(build_info.strIp,n1, n2,n3,n4); // 检查失败的原因，并给出详细的提示信息
        return FALSE;
    }
    return true;
}

BOOL CMainFrame::ConnectSubBuilding(Building_info build_info)
{
    CString g_strT3000LogString;
    CString strInfo;
    if(m_hCurCommunication!=NULL)
    {
        CloseHandle(m_hCurCommunication);
        m_hCurCommunication=NULL;
    }
    if (!((build_info.strIp.CompareNoCase(_T("9600")) ==0)||(build_info.strIp.CompareNoCase(_T("19200"))==0) ||(build_info.strIp.CompareNoCase(_T(""))) == 0))
    {

        /*}
        if (build_info.strProtocol.CompareNoCase(_T("Modbus TCP"))==0)
        {*/
        g_strT3000LogString.Format(_T("Trying to connect to %s,please waiting..."),build_info.strIp);
        CString* pstrInfo = new CString(g_strT3000LogString);
        ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));
        UINT n1,n2,n3,n4;
        if (ValidAddress(build_info.strIp,n1,n2,n3,n4)==FALSE)  // 验证NC的IP
        {


            CString StringIP;
            if(!GetIPbyHostName(build_info.strIp,StringIP))
            {
                AfxMessageBox(_T("Can not get a validate IP adreess from the domain name!"));
                return false;
            }
            CString strPort;
            m_nIpPort=_wtoi(build_info.strIpPort);
            g_CommunicationType=1;
            SetCommunicationType(g_CommunicationType);
            bool b=Open_Socket2(StringIP,m_nIpPort);
            CString strInfo;
            if(b)
            {
                strInfo.Format((_T("Open IP:%s successful")),build_info.strIp);//prompt info;
                SetPaneString(1,strInfo);
                return TRUE;
            }
            else
            {
                strInfo.Format((_T("Open IP:%s failure")),build_info.strIp);//prompt info;
                SetPaneString(1,strInfo);
                return FALSE;
            }
        }
        else
        {
            CString strPort;
            m_nIpPort=_wtoi(build_info.strIpPort);

            m_strIP=build_info.strIp;

            g_CommunicationType=1;
            SetCommunicationType(g_CommunicationType);
            bool b=Open_Socket2(build_info.strIp,m_nIpPort);
            CString strInfo;
            //	strInfo.Format((_T("Open IP:%s successful")),build_info.str3Ip);//prompt info;
            //	SetPaneString(1,strInfo);
            if(b)
            {
                strInfo.Format((_T("Open IP:%s successful")),build_info.strIp);//prompt info;
                SetPaneString(1,strInfo);
                return TRUE;
            }
            else
            {
                strInfo.Format((_T("Open IP:%s failure")),build_info.strIp);//prompt info;
                SetPaneString(1,strInfo);
                //ValidOpenFailure(build_info.strIp,n1, n2,n3,n4); // 检查失败的原因，并给出详细的提示信息
                return FALSE;
            }
        }
    }


    g_CommunicationType = 0;
    SetCommunicationType(g_CommunicationType);
    CString strComport = build_info.strComPort;
    CString strComNum = strComport.Mid(3);
    int nCom = _wtoi(strComNum);

    open_com(nCom);//open*************************************
    if(!is_connect())
    {

        //strInfo.Format(_T("COM: %d Connected: No"), nCom);
        strInfo.Format(_T("COM %d : Not available "), nCom);
        SetPaneString(1,strInfo);
        AfxMessageBox(strInfo);
        return FALSE;
    }
    else
    {
        strInfo.Format(_T("COM %d Connected: Yes"), nCom);
        SetPaneString(1,strInfo);
        Change_BaudRate(default_com1_port_baudrate);
        return TRUE;
    }
    return FALSE;
}

BOOL CMainFrame::ConnectDevice(tree_product tree_node)
{
    BOOL bRet =FALSE;
    CString strInfo;
    if(m_hCurCommunication!=NULL)
    {
        CloseHandle(m_hCurCommunication);
        m_hCurCommunication=NULL;
    }
    if (!((tree_node.BuildingInfo.strIp.CompareNoCase(_T("9600")) ==0)||(tree_node.BuildingInfo.strIp.CompareNoCase(_T("19200"))==0) ||(tree_node.BuildingInfo.strIp.CompareNoCase(_T(""))) == 0))
    {

        /*}
        if (build_info.strProtocol.CompareNoCase(_T("Modbus TCP"))==0)
        {*/

        //if(tree_node.protocol == PROTOCOL_REMOTE_IP)
        //{
        //	CString strIP;
        //	bool is_domain = false;
        //	strIP = m_str_curBuilding_Domain_IP;

        //	CStringArray temparray;
        //	SplitCStringA(temparray,strIP,_T("."));
        //	if((temparray.GetSize()==4))	//有3个  . 4段
        //	{
        //		CString temp_0;
        //		CString temp_1;
        //		CString temp_2;
        //		CString temp_3;
        //		temp_0 = temparray.GetAt(0);
        //		temp_1 = temparray.GetAt(1);
        //		temp_2 = temparray.GetAt(2);
        //		temp_3 = temparray.GetAt(3);

        //		if((Is_Dig_Num(temp_0)) && (Is_Dig_Num(temp_1)) && (Is_Dig_Num(temp_2)) && (Is_Dig_Num(temp_3)))
        //		{
        //			if(ValidAddress(strIP) == false)
        //			{

        //				return 0;
        //			}

        //		}
        //		else	//否则判断为 域名;
        //		{
        //			is_domain = true;
        //		}
        //	}
        //	else	//判断为 域名;
        //	{
        //		is_domain = true;
        //	}

        //	if(is_domain)
        //	{
        //		CString temp_host_ip;
        //		if(!GetIPbyHostName(m_str_curBuilding_Domain_IP,temp_host_ip))
        //		{
        //			if (pScan->m_eScanRemoteIPEnd->m_hObject)
        //			{
        //				pScan->m_eScanRemoteIPEnd->SetEvent();
        //			}
        //			//AfxMessageBox(_T("Can not get a validate IP adreess from the domain name!"));
        //			return 0;
        //		}
        //		Remote_IP_Address = temp_host_ip;
        //	}
        //	else
        //	{
        //		Remote_IP_Address = m_str_curBuilding_Domain_IP;
        //	}
        //}

        UINT n1,n2,n3,n4;
        if (ValidAddress(tree_node.BuildingInfo.strIp,n1,n2,n3,n4)==FALSE)  // 验证NC的IP
        {

            CString StringIP;
            if(!GetIPbyHostName(tree_node.BuildingInfo.strIp,StringIP))
            {
                AfxMessageBox(_T("Can not get a validate IP adreess from the domain name!"));
                return false;
            }
            CString strPort;
            m_nIpPort=tree_node.ncomport;//_wtoi(tree_node.ncomport);
            g_CommunicationType=1;
            SetCommunicationType(g_CommunicationType);
            bool b=Open_Socket2(StringIP,m_nIpPort);
            bRet =b;
            CString strInfo;
            if(b)
            {
                strInfo.Format((_T("Open IP:%s:%d successful")),tree_node.BuildingInfo.strIp,m_nIpPort);//prompt info;
                SetPaneString(1,strInfo);
                CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                CFileFind fFind;
                if(!fFind.FindFile(g_configfile_path))
                {
                    CString strInfo;
                    strInfo.Format(_T("%d"),g_CommunicationType);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
//  						strInfo.Format(_T("COM%d"),nCom);
//  						WritePrivateProfileStringW(_T("Setting"),_T("COM Port"),strInfo,g_configfile_path);
//  						strInfo.Format(_T("%d"),nCom);
//  						WritePrivateProfileStringW(_T("Setting"),_T("COM_Port"),strInfo,g_configfile_path);
//  						strInfo=_T("19200");
//  						WritePrivateProfileStringW(_T("Setting"),_T("Baudrate"),_T("19200"),g_configfile_path);


                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),StringIP,g_configfile_path);
                    strInfo.Format(_T("%d"),m_nIpPort);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);

                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }
                else
                {
                    CString strInfo;
                    strInfo.Format(_T("%d"),g_CommunicationType);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
// 						strInfo.Format(_T("COM%d"),nCom);
// 						WritePrivateProfileStringW(_T("Setting"),_T("COM Port"),strInfo,g_configfile_path);
// 						strInfo.Format(_T("%d"),nCom);
// 						WritePrivateProfileStringW(_T("Setting"),_T("COM_Port"),strInfo,g_configfile_path);
// 						strInfo=_T("19200");
// 						WritePrivateProfileStringW(_T("Setting"),_T("Baudrate"),_T("19200"),g_configfile_path);

                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),StringIP,g_configfile_path);
                    strInfo.Format(_T("%d"),m_nIpPort);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);

                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }

                return TRUE;
            }
            else
            {
                strInfo.Format((_T("Open IP:%s failure")),tree_node.BuildingInfo.strIp);//prompt info;
                SetPaneString(1,strInfo);
                return FALSE;
            }
        }
        else
        {
            CString strPort;
            m_nIpPort=tree_node.ncomport;//_wtoi(tree_node.BuildingInfo.strIpPort);

            m_strIP=tree_node.BuildingInfo.strIp;

            g_CommunicationType=1;
            SetCommunicationType(g_CommunicationType);
            bool b=Open_Socket2(tree_node.BuildingInfo.strIp,m_nIpPort);
            bRet =b;
            CString strTips;
            strTips.Format(_T("Try to connect %s ,Port:%d"),tree_node.BuildingInfo.strIp,m_nIpPort);
            //write_T3000_log_file(strTips);
            CString strInfo;
            //	strInfo.Format((_T("Open IP:%s successful")),build_info.str3Ip);//prompt info;
            //	SetPaneString(1,strInfo);
            if(b)
            {
                strInfo.Format((_T("Open IP:%s:%d successful")),tree_node.BuildingInfo.strIp,m_nIpPort);//prompt info;
                // write_T3000_log_file(strInfo);
                SetPaneString(1,strInfo);
                CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                CFileFind fFind;
                if(!fFind.FindFile(g_configfile_path))
                {
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("1"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),tree_node.BuildingInfo.strIp,g_configfile_path);
                    strInfo.Format(_T("%d"),m_nIpPort);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }
                else
                {
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),_T("1"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),tree_node.BuildingInfo.strIp,g_configfile_path);
                    strInfo.Format(_T("%d"),m_nIpPort);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }
                return TRUE;
            }
            else
            {
                strInfo.Format((_T("Open IP:%s failure")),tree_node.BuildingInfo.strIp);//prompt info;
                SetPaneString(1,strInfo);
                //write_T3000_log_file(strInfo);
                //ValidOpenFailure(build_info.strIp,n1, n2,n3,n4); // 检查失败的原因，并给出详细的提示信息
                return FALSE;
            }
        }
    }


    g_CommunicationType = 0;
    SetCommunicationType(g_CommunicationType);
    /*CString strComport = tree_node.BuildingInfo.strComPort;
    CString strComNum = strComport.Mid(3);
    int nCom = _wtoi(strComNum);*/
    int nCom = tree_node.ncomport;
    open_com(nCom);//open*************************************
    if(!is_connect())
    {

        //strInfo.Format(_T("COM: %d Connected: No"), nCom);
        strInfo.Format(_T("COM %d : Not available "), nCom);
        SetPaneString(1,strInfo);
        AfxMessageBox(strInfo);
        bRet =FALSE;
    }
    else
    {
        strInfo.Format(_T("COM %d Connected: Yes"), nCom);
        SetPaneString(1,strInfo);
        Change_BaudRate(default_com1_port_baudrate);
        CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
        CFileFind fFind;
        if(!fFind.FindFile(g_configfile_path))
        {
            CString strInfo;
            strInfo.Format(_T("%d"),g_CommunicationType);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
            strInfo.Format(_T("COM%d"),nCom);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
            strInfo.Format(_T("%d"),nCom);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);

            strInfo.Format(_T("%d"),default_com1_port_baudrate);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);



        }
        else
        {
            CString strInfo;
            strInfo.Format(_T("%d"),g_CommunicationType);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
            strInfo.Format(_T("COM%d"),nCom);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
            strInfo.Format(_T("%d"),nCom);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);

            strInfo.Format(_T("%d"),tree_node.baudrate);
            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);



        }


        bRet = TRUE;
    }
    bRet = is_connect();


    if (!bRet)
    {
        CheckConnectFailure(tree_node.BuildingInfo.strIp);



        m_nStyle=2;
        m_pTreeViewCrl->turn_item_image(tree_node.product_item ,false);//Can't connect to the device , it will show disconnection;
        tree_node.status_last_time[0] = false;
        tree_node.status_last_time[1] = false;
        tree_node.status_last_time[2] = false;

        return bRet;
    }
    else
    {
        m_nStyle=1;
        m_CurSubBuldingInfo=tree_node.BuildingInfo;
        m_pTreeViewCrl->turn_item_image(tree_node.product_item ,true);

        m_pTreeViewCrl->SetSelectItem(tree_node.product_item );//在线的时候才将颜色变红;
        m_pTreeViewCrl->SetSelectSerialNumber(tree_node.serial_number);
        g_selected_serialnumber = tree_node.serial_number;

    }
    return bRet;
}
void CMainFrame::CheckConnectFailure(const CString& strIP) // 检查失败的原因，并给出详细的提示信息
{
    USES_CONVERSION;
    LPCSTR szIP = W2A(strIP);
    DWORD dwIP = inet_addr(szIP);

    IN_ADDR ia;
    ia.S_un.S_addr = dwIP;

    //////////////////////////////////////////////////////////////////////////
    char hostname[256];
    int res = gethostname(hostname, sizeof(hostname));
    if(res != 0)
        return;

    hostent* pHostent = gethostbyname(hostname);
    if(pHostent==NULL)
        return;

    hostent& he = *pHostent;
    sockaddr_in sa;

    memcpy(&sa.sin_addr.s_addr, he.h_addr_list[0],he.h_length);

    //return   inet_ntoa(sa.sin_addr);
    CString strHostIP;
    strHostIP.Format(_T("%d.%d.%d.%d"), sa.sin_addr.S_un.S_un_b.s_b1,sa.sin_addr.S_un.S_un_b.s_b2,sa.sin_addr.S_un.S_un_b.s_b3,sa.sin_addr.S_un.S_un_b.s_b4);
    //AfxMessageBox(strIP);

    // 是否是同一子网
    if ( ia.S_un.S_un_b.s_b1 == sa.sin_addr.S_un.S_un_b.s_b1 &&
            ia.S_un.S_un_b.s_b2 == sa.sin_addr.S_un.S_un_b.s_b2 &&
            ia.S_un.S_un_b.s_b3 == sa.sin_addr.S_un.S_un_b.s_b3
       )
    {
        // 是同一子网，但是连接不上，那么提示检查设备连接
        CString strTip;
        strTip.Format(_T("Can not set up the connection with %s, please check its IP address and net cable. "), strIP);
        AfxMessageBox(strTip);
    }
    else
    {
        CString strTip;
        strTip.Format(_T("Your host IP is %s, and NC' IP is %s. They are not in same sub net, please reset your IP address. "),strHostIP, strIP);
        AfxMessageBox(strTip);
    }


}

#include "BuildingConfigration.h"

void CMainFrame::OnAddBuildingConfig()
{
    if(g_BuildingsetLevel==1)
    {
        CAfxMessageDialog dlg;
        CString strPromption;
        strPromption.LoadString(IDS_STRNOPRIVILEGE_BUILDING);
        dlg.SetPromtionTxt(strPromption);
        dlg.DoModal();
        return;
    }
    /*
    CMannageBuidingDlg Dlg;
    if(Dlg.DoModal()==IDOK)
    {
    //	CAddBuilding Dlg;
    //	Dlg.DoModal();
    }
    */

    bool temp_value = 	b_pause_refresh_tree;	//如果在Config界面选择building的时候就不要刷新Tree了.
    b_pause_refresh_tree = true;
    m_nStyle=4;
    Invalidate();
    CBuildingConfigration Dlg;

    //CAddBuilding Dlg;
    Dlg.DoModal();

    if(Dlg.m_bChanged)
    {

    }

    //ScanTstatInDB();
    b_pause_refresh_tree = temp_value;

    PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);

}

void CMainFrame::OnScanDevice()
{

    if(m_subNetLst.size()<=0)
    {
        AfxMessageBox(_T("Please Select a main building first."));
        return;
    }
    m_bScanFinished=FALSE;
    m_bScanALL=FALSE;
    g_bPauseMultiRead=TRUE;
    m_nStyle=3;
    Invalidate();
    Scan_Product();

}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if(REFRESH_TIMER==nIDEvent)
    {
        if (g_bEnableRefreshTreeView && m_bEnableRefreshTreeView && !g_bPauseMultiRead )
        {
// 			g_bEnableRefreshTreeView = FALSE;
//

// 			//AfxBeginThread(_FreshTreeView, this);
// 			//RefreshTreeView();
// 			((CT3000View*)m_pViews[0])->Fresh();
//
// 			g_bEnableRefreshTreeView = TRUE;
            ////if ((m_pRefreshThread)&&(g_bEnableRefreshTreeView==TRUE))	//Modify by Fance
            ////{
            ////	m_pRefreshThread->PostThreadMessage(WM_DOREFRESH,NULL,NULL);
            ////}
        }

        //
    }

    if(SCAN_TIMER==nIDEvent)
    {
        CString strTemp;
        if(m_bScanFinished)
        {
            CString strTemp;
            g_bPauseMultiRead=FALSE;
            KillTimer(SCAN_TIMER);
            m_wndWorkSpace.m_TreeCtrl.Invalidate();
            SetPaneString(BAC_SHOW_MISSION_RESULTS,_T("Scan finished!"));
        }
        else
        {
            CString strTemp;
            if (g_nStartID == -1) // 用这个来区分是scan TStat 还是scan NC
            {
                strTemp = _T("sending scan broadcast");
            }
            else
            {
                strTemp.Format(_T("from address ID %d to %d"),g_nStartID,g_nEndID);
            }

            CString strTip;
            strTip.Format(_T("Scanning %s, %s. Please wait."), g_strScanInfoPrompt, strTemp);

            CString* pstrInfo = new CString(strTip);
            ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));
        }
    }

    if(MONITOR_MOUSE_KEYBOARD_TIMER == nIDEvent)
    {
        unsigned long time_now = time(NULL);
        if(time_now - time_click > 5)
        {
            no_mouse_keyboard_event_enable_refresh = true;
        }
        CFrameWndEx::OnTimer(nIDEvent);
    }


    if(SAVE_PRODYCT_STATUS == nIDEvent)
    {
        //TRACE(_T("Main timer SAVE_PRODYCT_STATUS\r\n"));

        //m_pCon.CreateInstance(_T("ADODB.Connection"));
        //m_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);
        CBADO bado;
        bado.SetDBPath(g_strCurBuildingDatabasefilePath);
        bado.OnInitADOConn();

        for(int i=0; i<m_product.size(); i++) //用于更新 产品的状态，以便下次打开的时候直接显示上次关闭的时候的状态;
        {
            CString serial_number_temp;
            serial_number_temp.Format(_T("%u"),m_product.at(i).serial_number);
            CString execute_str;
            try
            {

                execute_str.Format(_T("update ALL_NODE set Online_Status = %d where Serial_ID = '%s'"),m_product.at(i).status,serial_number_temp);
                bado.m_pConnection->Execute(execute_str.GetString(),NULL,adCmdText);
            }
            catch(_com_error *e)
            {
                //AfxMessageBox(e->ErrorMessage());
            }

        }
        bado.CloseConn();
        //if(m_pCon->State)
        //	m_pCon->Close();

    }

    CString str;
    str.Format(_T("Addr:%d [Tx=%d Rx=%d : Err=%d]"), g_tstat_id, g_llTxCount, g_llRxCount, g_llTxCount-g_llRxCount);
    SetPaneString(0,str);

    CFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::ClearBuilding()
{

    //
    int n=m_buildingLst.size();
    m_pTreeViewCrl->DeleteAllItems();
    m_comportlist.clear();
//	m_subNetLst.clear();
    m_floorLst.clear();
    m_roomLst.clear();

    m_backgroundLst.clear();
//	m_buildingLst.clear();



}
void CMainFrame::SwitchToPruductType(int nIndex)
{
// 	CString strInfo;
// 	strInfo.Format(_T("CMainFrame::SwitchToPruductType(int nIndex):%d"),nIndex);
// 	SetPaneString(2, strInfo);

    CView* pNewView = m_pViews[nIndex];
    if (!pNewView)
        return;
    CView* pActiveView =GetActiveView();
    if ( !pActiveView )    // No currently active view
        return;

    if ( pNewView == pActiveView )    // Already there
    {
        goto here;
    }
    m_nCurView = nIndex;    // Store the new current view's index

    // exchange view window ID's so RecalcLayout() works
    UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
    ::SetWindowLong(pActiveView->m_hWnd, GWL_ID,
                    ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
    ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
    // Display and update the new current view - hide the old one
    pActiveView->ShowWindow(SW_HIDE);
    pNewView->ShowWindow(SW_SHOW);
    SetActiveView(pNewView);
    RecalcLayout();
    pNewView->Invalidate();

    //g_protocol = PROTOCOL_UNKNOW;//USE FOR identify the bacnet ip protocol

here:
    g_bPauseMultiRead = FALSE;//恢复主线程的刷新

    CString g_configfile_path =g_strExePth + g_strStartInterface_config;
    // 	//WrPrivateProfileInt(_T("Setting"),_T("Interface"),19,g_configfile_path);
    CString strInfo;
    strInfo.Format(_T("%d"),m_nCurView);
    WritePrivateProfileStringW(_T("T3000_START"),_T("Interface"),strInfo,g_configfile_path);
    strInfo.Format(_T("%u"),g_selected_serialnumber);
    WritePrivateProfileStringW(_T("T3000_START"),_T("SerialNumber"),strInfo,g_configfile_path);
    /* CString achive_file_path;
    CString temp_serial;
    temp_serial.Format(_T("%d.prg"),g_selected_serialnumber);
    achive_file_path = g_achive_folder + _T("\\") + temp_serial;
    Load_Product_Value_Cache(achive_file_path);
    g_tstat_id = product_register_value[6];*/

    switch(nIndex)
    {
    case DLG_T3000_VIEW:
    {
        m_nCurView=DLG_T3000_VIEW;
        ((CT3000View*)m_pViews[m_nCurView])->FreshIOGridTable();
        ((CT3000View*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_NETWORKCONTROL_VIEW:
    {
        m_nCurView=DLG_NETWORKCONTROL_VIEW;
        ((CNetworkControllView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_GRAPGIC_VIEW:
    {
        m_nCurView=DLG_GRAPGIC_VIEW;

        int nSerialNum=get_serialnumber();
        ((CGraphicView*)m_pViews[m_nCurView])->InitGraphic(nSerialNum,g_tstat_id);
    }
    break;
    case DLG_TRENDLOG_VIEW:
    {
        m_nCurView=DLG_TRENDLOG_VIEW;
    }
    break;
    case DLG_DIALOGCM5_VIEW:		//CM5
    {
        //m_nCurView=DLG_DIALOGCM5_VIEW;
        //((CDialogCM5*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOGT3_VIEW:	   //T3
    {
        m_nCurView =DLG_DIALOGT3_VIEW;
        ((CDialogT3*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOGMINIPANEL_VIEW://Mini Panel
    {
        m_nCurView = DLG_DIALOGMINIPANEL_VIEW;
        //((CDialgMiniPanel*)m_pViews[m_nCurView])->Fresh();
        //This is old MiniPanel ,basing on the modbus protocol.

    }
    break;
    case DLG_AIRQUALITY_VIEW://AirQuality
    {
        m_nCurView = DLG_AIRQUALITY_VIEW;
        ((CAirQuality*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_LIGHTINGCONTROLLER_VIEW:
    {
        m_nCurView = DLG_LIGHTINGCONTROLLER_VIEW;
        ((CLightingController*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_HUMCHAMBER:
    {
        m_nCurView=DLG_HUMCHAMBER;
        ((CNewHumChamberView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  DLG_CO2_VIEW:
    {
        m_nCurView = DLG_CO2_VIEW;
        ((CCO2_View*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  PM_CO2_NODE:
    {
        m_nCurView = DLG_CO2_VIEW;
        ((CCO2_View*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  DLG_CO2_NET_VIEW:
    {
        m_nCurView = DLG_CO2_NET_VIEW;
        ((CCO2NetView*)m_pViews[m_nCurView])->Fresh();
    }
    break;

    case  DLG_BACNET_VIEW:
    {
        m_nCurView = DLG_BACNET_VIEW;
        ((CDialogCM5_BacNet*)m_pViews[m_nCurView])->Fresh();
        //g_protocol = PROTOCOL_BACNET_IP;
    }
    break;
    case DLG_DIALOGT38I13O_VIEW:
    {
        m_nCurView=DLG_DIALOGT38I13O_VIEW;
        ((T38I13O*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOGT332AI_VIEW:
    {
        m_nCurView=DLG_DIALOGT332AI_VIEW;
        ((T332AI*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOGT38AI8AO :
    {
        m_nCurView=DLG_DIALOGT38AI8AO;
        ((T38AI8AO*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  DLG_DIALOGT36CT:
    {
        m_nCurView=DLG_DIALOGT36CT;
        ((T36CT*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOGT3PT10:
    {
        m_nCurView=DLG_DIALOGT3PT10;
        ((CT3RTDView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_PRESSURE_SENSOR:
    {
        m_nCurView=DLG_DIALOG_PRESSURE_SENSOR;
        ((CPressureSensorForm*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  DLG_DIALOG_TEMP_HUMSENSOR:
    {
        m_nCurView=DLG_DIALOG_TEMP_HUMSENSOR;
        ((CTempHumSensorForm*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case  DLG_DIALOG_DEFAULT_T3000_VIEW:
    {
        m_nCurView=DLG_DIALOG_DEFAULT_T3000_VIEW;
        ((T3000_Default_MainView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_T3_INPUTS_VIEW:
    {
        m_nCurView=DLG_DIALOG_T3_INPUTS_VIEW;
        ((CT3ModulesView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_T3_OUTPUTS_VIEW:
    {
        m_nCurView = DLG_DIALOG_T3_OUTPUTS_VIEW;
        ((CT3ModulesOutputDlg*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_CUSTOM_VIEW:
    {
        m_nCurView = DLG_DIALOG_CUSTOM_VIEW;
        ((CProductRegisterListView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_TSTAT_INPUT_VIEW:
    {
        m_nCurView = DLG_DIALOG_TSTAT_INPUT_VIEW;
        ((CTStatInputView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_TSTAT_OUTPUT_VIEW:
    {
        m_nCurView = DLG_DIALOG_TSTAT_OUTPUT_VIEW;
        ((CTStatOutputView*)m_pViews[m_nCurView])->Fresh();
    }
    break;
    case DLG_DIALOG_BOATMONITOR:
    {
        m_nCurView = DLG_DIALOG_BOATMONITOR;
        ((CBoatMonitorViewer*)m_pViews[m_nCurView])->Fresh();
    }
    break;
        //here
    }
}
void CMainFrame::SetPaneConnectionPrompt(CString strInfo)
{
    SetPaneString(2,strInfo);
}
void CMainFrame::SwitchToGraphicView()
{

    //if(((CT3000View*)m_pViews[0])->m_pSetPtDayDlg!=NULL)
    //	((CT3000View*)m_pViews[0])->m_pSetPtDayDlg->ShowWindow(SW_HIDE);


    SwitchToPruductType(DLG_GRAPGIC_VIEW);
}
void CMainFrame::OnAllNodeDatabase()
{
    bool temp_status = g_bPauseRefreshTree;
    g_bPauseRefreshTree = true;
    b_pause_refresh_tree = true;
    if(m_strCurMainBuildingName.IsEmpty())
        AfxMessageBox(_T("Please Select a Building First."));
    CAllNodesDiaolg Dlg;
    Dlg.SetBuildingMainName(m_strCurMainBuildingName);

    Dlg.DoModal();
    if(Dlg.m_bChanged)
    {
        ScanTstatInDB();
    }
    g_bPauseRefreshTree = temp_status;
    b_pause_refresh_tree = temp_status;
}
void CMainFrame::Scan_Product()
{
    /*
    if(m_subNetLst.size()<=0)
    {
    	AfxMessageBox(_T("Please add a building first."));
    	return;
    }
    */
    CString strTime;
    strTime=Get_NowTime();
    //开始时间

    CString g_strT3000LogString=_T("--------------------------------Scan Begin--------------------------------\n");

    //write_T3000_log_file(g_strT3000LogString);
    CString* pstrInfo = new CString(g_strT3000LogString);
    ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));

    g_strT3000LogString=_T("Scan begin Time: ");
    g_strT3000LogString+=strTime+_T("\n");;
    //write_T3000_log_file(g_strT3000LogString);
    //NET_WriteLogFile(g_strT3000LogString);
    pstrInfo = new CString(g_strT3000LogString);
    ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));
// 	if(m_pRs->State)
// 	m_pRs->Close();
// 	if(m_pCon->State)
// 	m_pCon->Close();

    ClearBuilding();


    HANDLE temphandle;//如果用户点击Scan，而 bacnet的线程还在继续工作，需要先结束这两个线程;
    if(bac_net_initial_once)
    {
        temphandle = Get_RS485_Handle();
        if(temphandle !=NULL)
        {
            TerminateThread((HANDLE)Get_Thread1(),0);
            TerminateThread((HANDLE)Get_Thread2(),0);

            CloseHandle(temphandle);
            Set_RS485_Handle(NULL);
            bac_net_initial_once = false;
        }
    }
    //g_pauseMultiReadEvent.SetEvent();
    //Sleep(500);

    // oldscan
    SetTimer(SCAN_TIMER,100,NULL);//lsc


//m_pThreadScan = AfxBeginThread(_ScanproductFun,this);
//* newscan


    g_bEnableRefreshTreeView = FALSE;
    g_bPauseRefreshTree = TRUE;
    if (m_pScanner != NULL)
    {
        delete m_pScanner;
        m_pScanner = NULL;
    }
    m_pScanner = new CTStatScanner;
    g_ScnnedNum=0;
    m_pScanner->SetParentWnd(this);
    m_pScanner->SetSubnetInfo(m_subNetLst);//vector<Building_info>& szSubnets);

    CString strMB485=_T("Modbus 485");
    CString strProtocol = m_subNetLst.at(m_nCurSubBuildingIndex).strProtocol;
    CString strBaudrate = m_subNetLst.at(m_nCurSubBuildingIndex).strBaudRate;
    m_pScanner->SetBaudRate(strBaudrate);

    CString strCom = m_subNetLst.at(m_nCurSubBuildingIndex).strComPort;
    CString tc = strCom.Mid(3);
    int nCom = _wtoi(tc);
    m_pScanner->SetComPort(nCom);

    g_nStartID = 1;
    g_nEndID = 254;
    if (m_pWaitScanDlg!=NULL)
    {
        delete m_pWaitScanDlg;
        m_pWaitScanDlg=NULL;
    }
    m_pWaitScanDlg = new CScanDbWaitDlg;
    m_pWaitScanDlg->SetTStatScaner(m_pScanner);
    m_pScanner->ScanAll();
    m_pScanner->m_scantype = 3;
    m_pWaitScanDlg->DoModal();

    m_bScanALL = TRUE;
//	close_com();
    //m_bScanFinished = FALSE;
    delete m_pWaitScanDlg;
    m_pWaitScanDlg = NULL;
//*/
}



CString CMainFrame::GetDeviceClassName(int nClassID)
{
    CString strClassName;
    switch(nClassID)
    {
    case 2:
        strClassName=g_strTstat5a;
        break;
    case 1:
        strClassName=g_strTstat5b;
        break;
    case 3:
        strClassName=g_strTstat5b;
        break;
    case 4:
        strClassName=g_strTstat5c;
        break;
    case 12:
        strClassName=g_strTstat5d;
        break;
    case PM_NC:
        strClassName=g_strnetWork;
        break;
    case NET_WORK_OR485_PRODUCT_MODEL:
        strClassName=g_strOR485;
        break;
    case 17:
        strClassName=g_strTstat5f;
        break;
    case 18:
        strClassName=g_strTstat5g;
        break;
    case 16:
        strClassName=g_strTstat5e;
        break;
    case PM_PM5E:
        strClassName=g_strTstat5e;
        break;
    case 19:
        strClassName=g_strTstat5h;
        break;
    case 7:
        strClassName=g_strTstat7;
        break;
    case 6:
        strClassName=g_strTstat6;
        break;
    case 13:
    case 14:
        break;
    default:
        strClassName=g_strTstat5a;
        break;
    }

    return strClassName;
}


void CMainFrame::OnMBP()
{
//     if (m_bDialogOpen == TRUE) return;
//     //m_pDlg->m_nColor = m_nClientColor;   // sets dialog's variables
//     //m_pDlg->m_sTitle = m_sMainWindowTitle;
// 	m_bDialogOpen = TRUE;
//     m_pDlg->Create();
}

//LONG CMainFrame::OnDlgClose(UINT wParam, LONG lParam)
//{
//	/*m_bDialogOpen = FALSE;*/
//	return 1;
//}

void CMainFrame::OnLabel()
{
}
void CMainFrame::OnLabe2()
{
}
void CMainFrame::OnLabe3()
{
}

void CMainFrame::Show_Wait_Dialog_And_SendConfigMessage()
{
#if 0
    for (int i=0; i<BAC_INPUT_GROUP; i++)
    {

        Write_Config_Info.Write_Input_Info[i].command = 0;
        Write_Config_Info.Write_Input_Info[i].device_id = 0;
        Write_Config_Info.Write_Input_Info[i].start_instance =0;
        Write_Config_Info.Write_Input_Info[i].end_instance =0;
        Write_Config_Info.Write_Input_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Input_Info[i].resend_count = 0;
        Write_Config_Info.Write_Input_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Input_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Input_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_OUTPUT_GROUP; i++)
    {

        Write_Config_Info.Write_Output_Info[i].command = 0;
        Write_Config_Info.Write_Output_Info[i].device_id = 0;
        Write_Config_Info.Write_Output_Info[i].start_instance =0;
        Write_Config_Info.Write_Output_Info[i].end_instance =0;
        Write_Config_Info.Write_Output_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Output_Info[i].resend_count = 0;
        Write_Config_Info.Write_Output_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Output_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Output_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_VARIABLE_GROUP; i++)
    {

        Write_Config_Info.Write_Variable_Info[i].command = 0;
        Write_Config_Info.Write_Variable_Info[i].device_id = 0;
        Write_Config_Info.Write_Variable_Info[i].start_instance =0;
        Write_Config_Info.Write_Variable_Info[i].end_instance =0;
        Write_Config_Info.Write_Variable_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Variable_Info[i].resend_count = 0;
        Write_Config_Info.Write_Variable_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Variable_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Variable_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_PROGRAM_GROUP; i++)
    {

        Write_Config_Info.Write_Program_Info[i].command = 0;
        Write_Config_Info.Write_Program_Info[i].device_id = 0;
        Write_Config_Info.Write_Program_Info[i].start_instance =0;
        Write_Config_Info.Write_Program_Info[i].end_instance =0;
        Write_Config_Info.Write_Program_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Program_Info[i].resend_count = 0;
        Write_Config_Info.Write_Program_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Program_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Program_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_PROGRAMCODE_GROUP; i++)
    {

        Write_Config_Info.Write_Programcode_Info[i].command = 0;
        Write_Config_Info.Write_Programcode_Info[i].device_id = 0;
        Write_Config_Info.Write_Programcode_Info[i].start_instance =0;
        Write_Config_Info.Write_Programcode_Info[i].end_instance =0;
        Write_Config_Info.Write_Programcode_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Programcode_Info[i].resend_count = 0;
        Write_Config_Info.Write_Programcode_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Programcode_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Programcode_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_PID_GROUP; i++)
    {

        Write_Config_Info.Write_Controller_Info[i].command = 0;
        Write_Config_Info.Write_Controller_Info[i].device_id = 0;
        Write_Config_Info.Write_Controller_Info[i].start_instance =0;
        Write_Config_Info.Write_Controller_Info[i].end_instance =0;
        Write_Config_Info.Write_Controller_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Controller_Info[i].resend_count = 0;
        Write_Config_Info.Write_Controller_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Controller_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Controller_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_SCREEN_GROUP; i++)
    {

        Write_Config_Info.Write_Screen_Info[i].command = 0;
        Write_Config_Info.Write_Screen_Info[i].device_id = 0;
        Write_Config_Info.Write_Screen_Info[i].start_instance =0;
        Write_Config_Info.Write_Screen_Info[i].end_instance =0;
        Write_Config_Info.Write_Screen_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Screen_Info[i].resend_count = 0;
        Write_Config_Info.Write_Screen_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Screen_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Screen_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_SCHEDULE_GROUP; i++)
    {

        Write_Config_Info.Write_Weekly_Info[i].command = 0;
        Write_Config_Info.Write_Weekly_Info[i].device_id = 0;
        Write_Config_Info.Write_Weekly_Info[i].start_instance =0;
        Write_Config_Info.Write_Weekly_Info[i].end_instance =0;
        Write_Config_Info.Write_Weekly_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Weekly_Info[i].resend_count = 0;
        Write_Config_Info.Write_Weekly_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Weekly_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Weekly_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_HOLIDAY_GROUP; i++)
    {

        Write_Config_Info.Write_Annual_Info[i].command = 0;
        Write_Config_Info.Write_Annual_Info[i].device_id = 0;
        Write_Config_Info.Write_Annual_Info[i].start_instance =0;
        Write_Config_Info.Write_Annual_Info[i].end_instance =0;
        Write_Config_Info.Write_Annual_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Annual_Info[i].resend_count = 0;
        Write_Config_Info.Write_Annual_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Annual_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Annual_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_MONITOR_GROUP; i++)
    {

        Write_Config_Info.Write_Monitor_Info[i].command = 0;
        Write_Config_Info.Write_Monitor_Info[i].device_id = 0;
        Write_Config_Info.Write_Monitor_Info[i].start_instance =0;
        Write_Config_Info.Write_Monitor_Info[i].end_instance =0;
        Write_Config_Info.Write_Monitor_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Monitor_Info[i].resend_count = 0;
        Write_Config_Info.Write_Monitor_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Monitor_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Monitor_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_SCHEDULECODE_GOUP; i++)
    {

        Write_Config_Info.Write_Weeklycode_Info[i].command = 0;
        Write_Config_Info.Write_Weeklycode_Info[i].device_id = 0;
        Write_Config_Info.Write_Weeklycode_Info[i].start_instance =0;
        Write_Config_Info.Write_Weeklycode_Info[i].end_instance =0;
        Write_Config_Info.Write_Weeklycode_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Weeklycode_Info[i].resend_count = 0;
        Write_Config_Info.Write_Weeklycode_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Weeklycode_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Weeklycode_Info[i].timeout_count = 0;
    }

    for (int i=0; i<BAC_HOLIDAYCODE_GROUP; i++)
    {

        Write_Config_Info.Write_Annualcode_Info[i].command = 0;
        Write_Config_Info.Write_Annualcode_Info[i].device_id = 0;
        Write_Config_Info.Write_Annualcode_Info[i].start_instance =0;
        Write_Config_Info.Write_Annualcode_Info[i].end_instance =0;
        Write_Config_Info.Write_Annualcode_Info[i].has_resend_yes_or_no = 0;
        Write_Config_Info.Write_Annualcode_Info[i].resend_count = 0;
        Write_Config_Info.Write_Annualcode_Info[i].task_result = BAC_RESULTS_UNKONW;
        Write_Config_Info.Write_Annualcode_Info[i].invoke_id = -1;
        //bac_input_read_results = 0;
        Write_Config_Info.Write_Annualcode_Info[i].timeout_count = 0;
    }
#endif

    if(hwait_write_thread==NULL)
    {
        hwait_write_thread =CreateThread(NULL,NULL,Send_Set_Config_Command_Thread,this,NULL, NULL);
    }
}

LRESULT CMainFrame::Delete_Write_New_Dlg(WPARAM wParam,LPARAM lParam)
{
    int message_type = wParam;
    switch(message_type)
    {
    case 0:
        if(WaitWriteDlg!=NULL)
        {
            Sleep(1000);
            delete WaitWriteDlg;
            WaitWriteDlg = NULL;

        }
        break;
    case 1:
        MessageBox(_T("Load config file failed , please try again!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        break;
    }

    return 0;
}



DWORD WINAPI  CMainFrame::Send_Set_Config_Command_Thread(LPVOID lpVoid)
{
    //Write_Config_Info
    CMainFrame *pParent = (CMainFrame *)lpVoid;

    read_write_bacnet_config = true;
    int end_temp_instance = 0;

    int resend_count;
    CString Mession_ret;

    int write_total_count = BAC_INPUT_GROUP +
                            BAC_OUTPUT_GROUP +
                            BAC_PROGRAM_GROUP +
                            BAC_VARIABLE_GROUP +
                            BAC_PID_GROUP +
                            BAC_PROGRAMCODE_GROUP +
                            BAC_SCREEN_GROUP +
                            BAC_MONITOR_GROUP +
                            BAC_SCHEDULE_GROUP +
                            BAC_HOLIDAY_GROUP +
                            BAC_SCHEDULECODE_GOUP +
                            BAC_HOLIDAYCODE_GROUP;


    int write_all_step = 1000 / write_total_count;
    int write_success_count = 0;
    int write_pos = 0;

    for (int i=0; i<BAC_INPUT_GROUP; i++)
    {
        end_temp_instance = BAC_READ_INPUT_REMAINDER + (BAC_READ_INPUT_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_INPUT_ITEM_COUNT)
            end_temp_instance = BAC_INPUT_ITEM_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEINPUT_T3000,(BAC_READ_INPUT_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write input form %d to %d success."),(BAC_READ_INPUT_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write input form %d to %d timeout."),(BAC_READ_INPUT_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }


    for (int i=0; i<BAC_OUTPUT_GROUP; i++)
    {
        end_temp_instance = BAC_READ_OUTPUT_REMAINDER + (BAC_READ_OUTPUT_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_OUTPUT_ITEM_COUNT)
            end_temp_instance = BAC_OUTPUT_ITEM_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEOUTPUT_T3000,(BAC_READ_OUTPUT_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write output form %d to %d success."),(BAC_READ_OUTPUT_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write output form %d to %d timeout."),(BAC_READ_OUTPUT_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_VARIABLE_GROUP; i++)
    {
        end_temp_instance = BAC_READ_VARIABLE_REMAINDER + (BAC_READ_VARIABLE_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_VARIABLE_ITEM_COUNT)
            end_temp_instance = BAC_VARIABLE_ITEM_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEVARIABLE_T3000,(BAC_READ_VARIABLE_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write variable form %d to %d success."),(BAC_READ_VARIABLE_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write variable form %d to %d timeout."),(BAC_READ_VARIABLE_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_PROGRAM_GROUP; i++)
    {
        end_temp_instance = BAC_READ_PROGRAM_REMAINDER + (BAC_READ_PROGRAM_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_PROGRAM_ITEM_COUNT)
            end_temp_instance = BAC_PROGRAM_ITEM_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEPROGRAM_T3000,(BAC_READ_PROGRAM_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write program form %d to %d success."),(BAC_READ_PROGRAM_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write program form %d to %d timeout."),(BAC_READ_PROGRAM_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }


    for (int i=0; i<BAC_SCHEDULECODE_GOUP; i++)
    {
        if(Write_Private_Data_Blocking(WRITETIMESCHEDULE_T3000,i,i) > 0)
        {
            Mession_ret.Format(_T("Write schedule form %d to %d success."),i,i);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write schedule form %d to %d timeout."),i,i);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_HOLIDAYCODE_GROUP; i++)
    {
        if(Write_Private_Data_Blocking(WRITEANNUALSCHEDULE_T3000,i,i) > 0)
        {
            Mession_ret.Format(_T("Write holiday form %d to %d success."),i,i);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write holiday form %d to %d timeout."),i,i);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_PID_GROUP; i++)
    {
        end_temp_instance = BAC_READ_PID_REMAINDER + (BAC_READ_PID_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_PID_COUNT)
            end_temp_instance = BAC_PID_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEPID_T3000,(BAC_READ_PID_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write PID form %d to %d success."),(BAC_READ_PID_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write PID form %d to %d timeout."),(BAC_READ_PID_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_SCREEN_GROUP; i++)
    {
        end_temp_instance = BAC_READ_SCREEN_REMAINDER + (BAC_READ_SCREEN_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_SCREEN_COUNT)
            end_temp_instance = BAC_SCREEN_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITESCREEN_T3000,(BAC_READ_SCREEN_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write screen form %d to %d success."),(BAC_READ_SCREEN_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write screen form %d to %d timeout."),(BAC_READ_SCREEN_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_HOLIDAY_GROUP; i++)
    {
        end_temp_instance = BAC_READ_HOLIDAY_REMAINDER + (BAC_READ_HOLIDAY_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_HOLIDAY_COUNT)
            end_temp_instance = BAC_HOLIDAY_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEHOLIDAY_T3000,(BAC_READ_HOLIDAY_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write holiday form %d to %d success."),(BAC_READ_HOLIDAY_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write holiday form %d to %d timeout."),(BAC_READ_HOLIDAY_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    for (int i=0; i<BAC_SCHEDULE_GROUP; i++)
    {
        end_temp_instance = BAC_READ_SCHEDULE_REMAINDER + (BAC_READ_SCHEDULE_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_SCHEDULE_COUNT)
            end_temp_instance = BAC_SCHEDULE_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITESCHEDULE_T3000,(BAC_READ_SCHEDULE_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write schedule form %d to %d success."),(BAC_READ_SCHEDULE_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write schedule form %d to %d timeout."),(BAC_READ_SCHEDULE_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }


    for (int i=0; i<BAC_MONITOR_GROUP; i++)
    {
        end_temp_instance = BAC_READ_MONOTOR_REMAINDER + (BAC_READ_MONITOR_GROUP_NUMBER)*i ;
        if(end_temp_instance >= BAC_MONITOR_COUNT)
            end_temp_instance = BAC_MONITOR_COUNT - 1;
        if(Write_Private_Data_Blocking(WRITEMONITOR_T3000,(BAC_READ_MONITOR_GROUP_NUMBER)*i,end_temp_instance) > 0)
        {
            Mession_ret.Format(_T("Write monitor form %d to %d success."),(BAC_READ_MONITOR_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            write_success_count ++ ;
            Sleep(SEND_COMMAND_DELAY_TIME);
        }
        else
        {
            Mession_ret.Format(_T("Write monitor form %d to %d timeout."),(BAC_READ_MONITOR_GROUP_NUMBER)*i,end_temp_instance);
            SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
            goto write_end_thread;
        }
        g_progress_persent = write_success_count * 100 /write_total_count;
    }





    for (int i=0; i<BAC_PROGRAMCODE_GROUP; i++)
    {

        int npart = (program_code_length[i] / 401) + 1;


        bool b_program_status = true;
        for (int j=0; j<npart; j++)
        {

            if(WriteProgramData_Blocking(g_bac_instance,WRITEPROGRAMCODE_T3000,i,i,j)> 0)
            {
                Mession_ret.Format(_T("Write program %d part %d success."),i,j+1);
                SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
                Sleep(SEND_COMMAND_DELAY_TIME);
                continue;
            }
            else
            {
                Mession_ret.Format(_T("Write program %d part %d timeout."),i,j+1);
                SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
                goto write_end_thread;
            }
        }
        write_success_count ++ ;
        g_progress_persent = write_success_count * 100 /write_total_count;
    }

    Mession_ret.Format(_T("Write config file success."));
    SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
    g_progress_persent = 100;

    read_write_bacnet_config = false;
    hwait_write_thread = NULL;
    return 0;
write_end_thread:
    g_progress_persent = 0;
    read_write_bacnet_config = false;
    hwait_write_thread = NULL;
    Mession_ret.Format(_T("Load config file Timeout,Please Try again."));
    SetPaneString(BAC_SHOW_MISSION_RESULTS,Mession_ret);
    AfxMessageBox(_T("Load config file Timeout,Please Try again."));
    return 2;
}

LRESULT  CMainFrame::ReadConfigFromDeviceMessageCallBack(WPARAM wParam, LPARAM lParam)
{
    bool msg_result=WRITE_FAIL;
    msg_result = MKBOOL(wParam);
    if(msg_result)
    {
        SaveBacnetConfigFile(SaveConfigFilePath);
    }
    return 0;
}
LRESULT CMainFrame::Refresh_RX_TX_Count(WPARAM wParam, LPARAM lParam)
{
    int ret = (int)wParam;
    if(ret == 1)
    {
        Set_Communication_Count(1,g_bac_instance);//成功，计数+1

        m_pTreeViewCrl->turn_item_image(selected_tree_item ,true);
        //SetPaneConnectionPrompt(_T("Online"));
    }
    else
        Set_Communication_Count(0,g_bac_instance);

    return 0;
}

LRESULT  CMainFrame::AllWriteMessageCallBack(WPARAM wParam, LPARAM lParam)
{
    _MessageInvokeIDInfo *pInvoke =(_MessageInvokeIDInfo *)lParam;
    bool msg_result=WRITE_FAIL;
    msg_result = MKBOOL(wParam);
    CString Show_Results;
    CString temp_cs = pInvoke->task_info;
    if(msg_result)
    {

        for (int i=0; i<BAC_INPUT_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Input_Info[i].invoke_id)
                Write_Config_Info.Write_Input_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_OUTPUT_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Output_Info[i].invoke_id)
                Write_Config_Info.Write_Output_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_VARIABLE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Variable_Info[i].invoke_id)
                Write_Config_Info.Write_Variable_Info[i].task_result = true;
        }
        for (int i=0; i<BAC_PROGRAM_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Program_Info[i].invoke_id)
                Write_Config_Info.Write_Program_Info[i].task_result = true;
        }

        //for (int i=0;i<BAC_PROGRAMCODE_GROUP;i++)
        //{
        //	if(pInvoke->Invoke_ID==Write_Config_Info.Write_Programcode_Info[i].invoke_id)
        //		Write_Config_Info.Write_Programcode_Info[i].task_result = true;
        //}


        for (int i=0; i<BAC_PID_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Controller_Info[i].invoke_id)
                Write_Config_Info.Write_Controller_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_SCREEN_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Screen_Info[i].invoke_id)
                Write_Config_Info.Write_Screen_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_SCHEDULE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Weekly_Info[i].invoke_id)
                Write_Config_Info.Write_Weekly_Info[i].task_result = true;
        }
        for (int i=0; i<BAC_SCHEDULECODE_GOUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Weeklycode_Info[i].invoke_id)
                Write_Config_Info.Write_Weeklycode_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_HOLIDAY_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Annual_Info[i].invoke_id)
                Write_Config_Info.Write_Annual_Info[i].task_result = true;
        }
        for (int i=0; i<BAC_HOLIDAYCODE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Annualcode_Info[i].invoke_id)
                Write_Config_Info.Write_Annualcode_Info[i].task_result = true;
        }

        for (int i=0; i<BAC_MONITOR_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Monitor_Info[i].invoke_id)
                Write_Config_Info.Write_Monitor_Info[i].task_result = true;
        }



        Show_Results = temp_cs + _T("Success!");
        SetPaneString(BAC_SHOW_MISSION_RESULTS,Show_Results);
        //TRACE(Show_Results + _T("\r\n"));
        //MessageBox(_T("Bacnet operation success!"));
    }
    else
    {

        for (int i=0; i<BAC_INPUT_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Input_Info[i].invoke_id)
                Write_Config_Info.Write_Input_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_OUTPUT_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Output_Info[i].invoke_id)
                Write_Config_Info.Write_Output_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_VARIABLE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Variable_Info[i].invoke_id)
                Write_Config_Info.Write_Variable_Info[i].task_result = false;
        }
        for (int i=0; i<BAC_PROGRAM_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Program_Info[i].invoke_id)
                Write_Config_Info.Write_Program_Info[i].task_result = false;
        }

        //for (int i=0;i<BAC_PROGRAMCODE_GROUP;i++)
        //{
        //	if(pInvoke->Invoke_ID==Write_Config_Info.Write_Programcode_Info[i].invoke_id)
        //		Write_Config_Info.Write_Programcode_Info[i].task_result = false;
        //}

        for (int i=0; i<BAC_PID_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Controller_Info[i].invoke_id)
                Write_Config_Info.Write_Controller_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_SCREEN_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Screen_Info[i].invoke_id)
                Write_Config_Info.Write_Screen_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_SCHEDULE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Weekly_Info[i].invoke_id)
                Write_Config_Info.Write_Weekly_Info[i].task_result = false;
        }
        for (int i=0; i<BAC_SCHEDULECODE_GOUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Weeklycode_Info[i].invoke_id)
                Write_Config_Info.Write_Weeklycode_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_HOLIDAY_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Annual_Info[i].invoke_id)
                Write_Config_Info.Write_Annual_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_HOLIDAYCODE_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Annualcode_Info[i].invoke_id)
                Write_Config_Info.Write_Annualcode_Info[i].task_result = false;
        }

        for (int i=0; i<BAC_MONITOR_GROUP; i++)
        {
            if(pInvoke->Invoke_ID==Write_Config_Info.Write_Monitor_Info[i].invoke_id)
                Write_Config_Info.Write_Monitor_Info[i].task_result = false;
        }

        Show_Results = temp_cs + _T("Fail!");
        SetPaneString(BAC_SHOW_MISSION_RESULTS,Show_Results);
        //TRACE(Show_Results + _T("\r\n"));
        //AfxMessageBox(Show_Results);
        //MessageBox(_T("Bacnet operation fail!"));
    }

    if(pInvoke)
        delete pInvoke;
    return 0;
}

void CMainFrame::SaveConfigFile()
{
    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == PROTOCOL_BIP_TO_MSTP) || (g_protocol == MODBUS_BACNET_MSTP))
    {
        MainFram_hwd = this->m_hWnd;

        CFileDialog dlg(false,_T("*.prg"),_T(" "),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("prg files (*.prg)|*.prg|All Files (*.*)|*.*||"),NULL,0);
        if(IDOK==dlg.DoModal())
        {

            SaveConfigFilePath=dlg.GetPathName();
            CFileFind cfindtempfile;
            if(cfindtempfile.FindFile(SaveConfigFilePath))
            {
                DeleteFile(SaveConfigFilePath);
            }

            //协议时bacnet ，用户点击 File save时 先调用线程读取所有需要存的资料；在发送消息回来 调用SaveBacnetConfigFile;
            //::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_SVAE_CONFIG);

            if(g_protocol == PROTOCOL_BACNET_IP)
            {
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,TYPE_SVAE_CONFIG,NULL);
            }
            else
            {
                Create_Thread_Read_Item(TYPE_ALL);
            }


        }
        else
        {
            SaveConfigFilePath.Empty();
        }





        //	SaveBacnetConfigFile();
        return;
    }
    int nret=0;
    g_bEnableRefreshTreeView = FALSE;
    int IDFlag=read_one(g_tstat_id,7);
    product_register_value[7]=IDFlag;
    if(IDFlag<=0)
        return;
    float version=get_curtstat_version();
    CString strFilter;
    CString strFilename;
    strFilter =_T( "Text File|*.txt|All File|*.*|");
    CFileDialog dlg(false,_T("txt"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,strFilter);
    if (dlg.DoModal() != IDOK)
        return;
    strFilename=dlg.GetPathName();

    BeginWaitCursor();
    CString strTips = _T("T3000 is ready to save config file, start now?");

    SetPaneString(1, strTips);
    //AfxMessageBox(strTips);

    if(product_register_value[7]==100||product_register_value[7]==PM_LightingController)//NC
    {
        strTips.Format(_T("Config file \" %s \" is saving, please waiting..."), strFilename);
        SetPaneString(1, strTips);
        if (product_register_value[7]==100)
        {
            save_schedule_2_file((LPTSTR)(LPCTSTR)strFilename,g_tstat_id);
        }
        else
        {
            save_schedule_2_file_LC((LPTSTR)(LPCTSTR)strFilename,g_tstat_id);
        }


        strTips.Format(_T("Config file \" %s \" saved successful."), strFilename);
        SetPaneString(1, strTips);
    }
    else if (product_register_value[7]==PM_T3PT10||
             product_register_value[7]==PM_T3IOA||
             product_register_value[7]==PM_T332AI||
             product_register_value[7]== PM_T38AI16O||
             product_register_value[7]==PM_T38I13O||
             product_register_value[7]==PM_T3PERFORMANCE||
             product_register_value[7]==PM_T34AO||
             product_register_value[7]==PM_T36CT ||
             product_register_value[7] == PM_T322AI||
             product_register_value[7] == PM_T38AI8AO6DO
            )
    {
        strTips.Format(_T("Config file \" %s \" is saving, please waiting..."), strFilename);
        SetPaneString(1, strTips);

        save_T3Modules_file((LPTSTR)(LPCTSTR)strFilename,g_tstat_id);

        strTips.Format(_T("Config file \" %s \" saved successful."), strFilename);
        SetPaneString(1, strTips);
    }
    else if ((product_register_value[7] == PM_TSTAT6)||(product_register_value[7] == PM_TSTAT7)||(product_register_value[7] == PM_TSTAT5i)||(product_register_value[7] == PM_TSTAT8))
    {

        int index = 0;


        memcpy(product_register_value,tempchange,sizeof(product_register_value));


        Save2File_ForTwoFilesTSTAT67((LPTSTR)(LPCTSTR)strFilename);


        strTips.Format(_T("Config file \" %s \" saved successful."), strFilename);

        SetPaneString(3, strTips);
        //AfxMessageBox(strTips);
    }
    else if (product_register_value[7] == PM_CO2_NODE)
    {
        Save2File_ForCO2Node((LPTSTR)(LPCTSTR)strFilename);
    }
    else//save tstat config file:
    {
        //?????
        /*	nret=write_one(g_tstat_id,MODBUS_FAN_GRIDPOINT,4);
        	nret=write_one(g_tstat_id,MODBUS_MODE_GRIDPOINT,0);
        	nret=write_one(g_tstat_id,MODBUS_HOLD_GRIDPOINT,0);
        	nret=write_one(g_tstat_id,MODBUS_CONFIGURATION,0);*/
        //int nSpecialValue=read_one(g_tstat_id,326);

        //if(nSpecialValue==1)
        //{
        ////	write_one(g_tstat_id,324,0);
        //}
        Save2File_ForTwoFiles((LPTSTR)(LPCTSTR)strFilename);


        strTips.Format(_T("Config file \" %s \" saved successful."), strFilename);

        SetPaneString(1, strTips);
        //AfxMessageBox(strTips);
// 		CMFCStatusBar * pStatusBar=NULL;
// 		if(AfxGetMainWnd()->GetActiveWindow()==NULL)//if this function is called by a thread ,return
// 			return;
// 		pStatusBar = (CMFCStatusBar *) AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);

    }

    EndWaitCursor();
    g_bEnableRefreshTreeView = TRUE;
}

LRESULT CMainFrame::OnCreateStatusBarWindow(WPARAM wParam, LPARAM lParam)
{

    b_statusbarthreadflag = true; // enable refresh status bar status;
    statusbar =new CMyStatusbarCtrl;
    statusbar->Create(IDD_DIALOG_STATUSBAR,this);
    statusbar->ShowWindow(SW_SHOW);
    CRect temprec;
    m_wndStatusBar.GetWindowRect(&temprec);
    statusbar->SetWindowPos(this,temprec.left,temprec.top,temprec.Width(),temprec.Height(),SWP_NOACTIVATE | SWP_SHOWWINDOW );
    b_create_status = true;
    return 1;
}


LRESULT CMainFrame::OnFreshStatusBar(WPARAM wParam, LPARAM lParam)
{
//pStatusBar->SetPaneText(nIndext,str.GetString());
    status_info*  pinfoStatusbar;
    pinfoStatusbar=(status_info*)wParam;
    //pinfoStatusbar.nIndex=nIndext;
//	infoStatusbar.strInfoText=str;
    m_wndStatusBar.SetPaneText(pinfoStatusbar->nIndex,pinfoStatusbar->strInfoText);


    return 1;
}


void CMainFrame::OnDestroy()
{

    OnDisconnect();

    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();
#if 1
    g_mstp_flag=FALSE;
    for(int i=0; i<m_product.size(); i++) //用于更新 产品的状态，以便下次打开的时候直接显示上次关闭的时候的状态;
    {
        CString serial_number_temp;
        serial_number_temp.Format(_T("%u"),m_product.at(i).serial_number);
        CString execute_str;
        try
        {

            execute_str.Format(_T("update ALL_NODE set Online_Status = %d where Serial_ID = '%s'"),m_product.at(i).status,serial_number_temp);
            bado.m_pConnection->Execute(execute_str.GetString(),NULL,adCmdText);
        }
        catch(_com_error *e)
        {
            //AfxMessageBox(e->ErrorMessage());
        }

    }
    bado.CloseConn();


    //close_T3000_log_file();
    m_Input_data.clear();
    m_Variable_data.clear();
    m_Output_data.clear();
    m_Program_data.clear();
    m_Weekly_data.clear();
    m_Annual_data.clear();
    m_Schedual_Time_data.clear();
    m_controller_data.clear();
    m_screen_data.clear();
    m_monitor_data.clear();
    m_alarmlog_data.clear();
    m_Tstat_data.clear();
    m_alarmlog_data.clear();
    m_customer_unit_data.clear();
    m_user_login_data.clear();
    m_graphic_label_data.clear();
    m_remote_point_data.clear();
    //CDialogInfo *pDialogInfo = NULL;
    try
    {
//  		if(pDialogInfo==NULL)
//  		{
// 			pDialogInfo = new CDialogInfo;
// 			pDialogInfo->Create(IDD_DIALOG_INFO,this);
// 			pDialogInfo->ShowWindow(SW_SHOW);
// 			pDialogInfo->CenterWindow();
// 			pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Processing Information,please wait..."));
// 		    }






        int temp =1;

        UpdataSlider(temp);
        b_statusbarthreadflag = FALSE; //close the status bar thread;
        g_bEnableRefreshTreeView = FALSE;
        HTREEITEM htiSel = m_pTreeViewCrl->GetSelectedItem();
        //SaveTreeNodeRecordToReg(htiSel);

        for(int i=0; i<WINDOW_TAB_COUNT ; i++)
        {
            if(pDialog[i]!=NULL)
            {
                delete pDialog[i];
                pDialog[i]=NULL;
            }
        }
        if(Add_Label_Window !=NULL)
        {
            delete Add_Label_Window;
            Add_Label_Window = NULL;
        }

        if(statusbar != NULL)
        {
            delete statusbar;
            statusbar = NULL;
        }

        if(DebugWindow !=NULL)
        {
            delete DebugWindow;
            DebugWindow = NULL;
        }

        for (int i=0; i<14; i++)
        {
            UnregisterHotKey(GetSafeHwnd(), m_MainHotKeyID[i]);
        }
        UnregisterHotKey(GetSafeHwnd(), 1111);
        UnregisterHotKey(GetSafeHwnd(), 1112);


        g_killMultiReadEvent.SetEvent();

        Sleep(500);//wait for the end of the thread.

        if (WaitForSingleObject(m_pFreshMultiRegisters->m_hThread, 1000) != WAIT_OBJECT_0)

            //Sleep(500);//wait for the end of the thread.
            if (m_pFreshMultiRegisters)

            {
                if (WaitForSingleObject(m_pFreshMultiRegisters->m_hThread, 3000) == WAIT_OBJECT_0)
                {

                }
                else
                {
                    BOOL bRet = TerminateThread(m_pFreshMultiRegisters->m_hThread,0);
                    //delete m_pFreshMultiRegisters;
                    m_pFreshMultiRegisters=NULL;
                }

            }
        if (WaitForSingleObject(m_pFreshTree->m_hThread, 1000) != WAIT_OBJECT_0)
            if (m_pFreshTree)

            {
                if (WaitForSingleObject(m_pFreshTree->m_hThread, 3000) == WAIT_OBJECT_0)
                {

                }
                else
                {
                    BOOL bRet = TerminateThread(m_pFreshTree->m_hThread,0);
                    //delete m_pFreshMultiRegisters;
                    m_pFreshTree=NULL;
                }

            }
        if(CM5_hThread!=NULL)
            TerminateThread(CM5_hThread,0);
        if(CM5_UI_Thread!=NULL)
            TerminateThread(CM5_UI_Thread,0);
        if(hDeal_thread!=NULL)
            TerminateThread(hDeal_thread,0);
        if(hThread!=NULL)
            TerminateThread(hThread,0);
        if(m_pFreshTree!=NULL)
            TerminateThread(m_pFreshTree,0);
        // 结束线程

        if (m_pRefreshThread)
        {
            HANDLE hp=m_pRefreshThread->m_hThread;
            g_bEnableRefreshTreeView = FALSE;
            PostThreadMessage(m_pRefreshThread->m_nThreadID,  WM_QUIT,0,0);
            g_bPauseRefreshTree = true;
            if (WaitForSingleObject(hp, 1000) != WAIT_OBJECT_0)

                if (WaitForSingleObject(m_pRefreshThread->m_hThread, 100) == WAIT_OBJECT_0)
                {
                }
                else
                {
                    TerminateThread(m_pRefreshThread->m_hThread, 0);

                }
            //CloseHandle(hp);
            //m_pRefreshThread->Delete();
        }


        SetCommunicationType(0);
        close_com(); // added by zgq:12-16-2011
        SetCommunicationType(1);
        close_com();

        close_T3000_log_file();


        if (m_pDialogInfo!=NULL)
        {
            delete m_pDialogInfo;
            m_pDialogInfo = NULL;
        }
#endif



    }
    catch (...)//这个无效，当pDialogInfo->Create(IDC_STATIC_INFO,this);中的ID写错时，这个函数没有throw抛出错误，所以捕获不到
    {
        Sleep(1);
    }


    CFrameWndEx::OnDestroy();
    // TODO: Add your message handler code here
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    if(message==WM_MYMSG_REFRESHBUILDING)
    {
        //Sleep(1000);
        //AfxMessageBox(_T("There is no default building,please select a building First."));
        BOOL bTemp = g_bEnableRefreshTreeView ;
        g_bEnableRefreshTreeView = FALSE;
        ScanTstatInDB();

        int temp_select_serial = m_pTreeViewCrl->GetSelectSerialNumber();
        bool find_serial_number_device = false;	//如果重新加载数据库，没有发现选中的那个设备 序列号，就说明可能被删掉了;需要退出当前界面 切换至初始界面;
        HTREEITEM temp_htree;
        for (int i=0; i<m_product.size(); i++)
        {
            if(temp_select_serial == m_product.at(i).serial_number)
            {
                temp_htree = m_product.at(i).product_item;
                m_pTreeViewCrl->SetSelectItem(temp_htree);
                find_serial_number_device = true;
                selected_product_index = i;//重新加载 产品列表的时候 选中上次选中的设备;
                break;
            }
        }

        if(!find_serial_number_device)
            SwitchToPruductType(DLG_DIALOG_DEFAULT_BUILDING);

        g_bEnableRefreshTreeView |= bTemp;
        return 0;
    }
    else if (message==WM_SHOW_PANNELINFOR)
    {
        CString* pStr = (CString*)(wParam);
        int ret = (int)lParam;
        SetPaneString(ret,*pStr);
        delete pStr;
        return 0;
    }

    return CFrameWndEx::WindowProc(message, wParam, lParam);
}
void CMainFrame::OnChangeAdminPassword()
{


    CChangePasswordDlg dlg;
    //dlg.DoModel();
    dlg.DoModal();

}
void CMainFrame::OnUserMannageMent()
{
    CManageAccountDlg Dlg;
    Dlg.DoModal();
}
void CMainFrame::OnUserLogin()
{
    CLoginDlg Dlg(g_buser_log_in);
    Dlg.DoModal();

}
void CMainFrame::OnUserMannageMentUpdate(CCmdUI *pCmdUI)
{
    if(g_UserLevel==0)
        pCmdUI->Enable(true);
    else
        pCmdUI->Enable(false);
}

void CMainFrame::GetIONanme()
{
    try
    {


        /*_ConnectionPtr m_ConTmp;
        _RecordsetPtr m_RsTmp;
        m_ConTmp.CreateInstance("ADODB.Connection");
        m_RsTmp.CreateInstance("ADODB.Recordset");
        m_ConTmp->Open(g_strDatabasefilepath.GetString(),"","",adModeUnknown);
        */

        CBADO bado;
        bado.SetDBPath(g_strCurBuildingDatabasefilePath);
        bado.OnInitADOConn();

        CString strSerial;
        strSerial.Format(_T("%u"),g_selected_serialnumber);
        strSerial.Trim();
        CString strsql;
        strsql.Format(_T("select * from IONAME where SERIAL_ID = '%s'"),strSerial);
        //m_RsTmp->Open((_variant_t)strsql,_variant_t((IDispatch *)m_ConTmp,true),adOpenStatic,adLockOptimistic,adCmdText);
        bado.m_pRecordset=bado.OpenRecordset(strsql);
        if(VARIANT_FALSE==bado.m_pRecordset->EndOfFile)
        {
            CString str_temp;
            str_temp.Empty();
            _variant_t temp_variant;

            temp_variant=bado.m_pRecordset->GetCollect("SENSORNAME");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Internal Sensor");
            g_strSensorName=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT1");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 1");
            g_strInName1=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT2");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 2");
            g_strInName2=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT3");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 3");
            g_strInName3=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT4");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 4");
            g_strInName4=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT5");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 5");
            g_strInName5=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT6");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 6");
            g_strInName6=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT7");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 7");
            g_strInName7=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT8");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Input 8");
            g_strInName8=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("INPUT9");
            //	temp_variant=m_RsTmp->GetCollect("Humidity Sensor");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Humidity Sensor");
            g_strInHumName=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT1");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 1");
            g_strOutName1=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT2");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 2");
            g_strOutName2=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT3");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 3");
            g_strOutName3=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT4");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 4");
            g_strOutName4=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT5");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 5");
            g_strOutName5=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT6");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 6");
            g_strOutName6=str_temp;

            temp_variant=bado.m_pRecordset->GetCollect("OUTPUT7");
            if(temp_variant.vt!=VT_NULL)
                str_temp=temp_variant;
            else
                str_temp=_T("Output 7");
            g_strOutName7=str_temp;

            g_strInHumName = _T("Humidity Sensor");
            g_strInCO2=_T("CO2 Sensor");
            g_strLightingSensor=_T("Lighting Sensor");
        }
        else
        {
            g_strSensorName =_T("Internal Temp Sensor");
            g_strInName1=_T("Input 1");
            g_strInName2=_T("Input 2");
            g_strInName3=_T("Input 3");
            g_strInName4=_T("Input 4");
            g_strInName5=_T("Input 5");
            g_strInName6=_T("Input 6");
            g_strInName7=_T("Input 7");
            g_strInName8=_T("Input 8");
            g_strLightingSensor=_T("Lighting Sensor");
            g_strInHumName = _T("Humidity Sensor");
            g_strInCO2=_T("CO2 Sensor");

            g_strOutName1=_T("Output 1");
            g_strOutName2=_T("Output 2");
            g_strOutName3=_T("Output 3");
            g_strOutName4=_T("Output 4");
            g_strOutName5=_T("Output 5");
            g_strOutName6=_T("Output 6");
            g_strOutName7=_T("Output 7");
            g_strOutName8=_T("Output 8");


        }
        bado.CloseRecordset();
        bado.CloseConn();
        /*if(m_RsTmp->State)
        	m_RsTmp->Close();
        if(m_ConTmp->State)
        	m_ConTmp->Close();	*/

    }
    catch (...)
    {

    }



}

void CMainFrame::OnHelp()
{
    //CString strHelp=g_strExePth+_T("The Instruction of T3000 .txt");
    //::HtmlHelp(NULL, strHelp, HH_DISPLAY_TOPIC, 0);
    //ShellExecute(NULL, _T("open"), strHelp, NULL, NULL, SW_SHOWNORMAL);
    HWND hWnd;

//  	if(pHelpInfo->dwContextId > 0) hWnd = ::HtmlHelp((HWND)pHelpInfo->hItemHandle, theApp.m_szHelpFile, HH_HELP_CONTEXT, pHelpInfo->dwContextId);
//  	else
    hWnd =  ::HtmlHelp(NULL, theApp.m_szHelpFile, HH_HELP_CONTEXT, IDH_TOPIC_OVERVIEW);
    //return (hWnd != NULL);

//      CGraphicModelDlg dlg;
//      dlg.DoModal();

}
void CMainFrame::OnImportDatase()
{
    CImportDatabaseDlg Dlg;
    Dlg.DoModal();

}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{

    if (m_pDialogInfo->IsWindowVisible())
    {
        if (pMsg->message == WM_LBUTTONDOWN||pMsg->message == WM_RBUTTONDOWN)
        {
            m_pDialogInfo->ShowWindow(SW_HIDE);
        }
    }


    if (pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == m_wndStatusBar.GetSafeHwnd())
    {
        CRect rect;
        CPoint pt;
        pt = pMsg->pt;
        m_wndStatusBar.GetItemRect(3,&rect);
        m_wndStatusBar.ClientToScreen(&rect);
        if(PtInRect(&rect,pt))
        {
            //AfxMessageBox(_T("3"));
            CString strHelp=g_strExePth+_T("T3000.log");
            //::HtmlHelp(NULL, strHelp, HH_DISPLAY_TOPIC, 0);
            ShellExecute(NULL, _T("open"), strHelp, NULL, NULL, SW_SHOWNORMAL);
        }
        m_wndStatusBar.GetItemRect(2,&rect);
        m_wndStatusBar.ClientToScreen(&rect);
        if(PtInRect(&rect,pt))
        {
            //AfxMessageBox(_T("2"));
        }
    }
    if((pMsg->message == WM_KEYDOWN ) || (pMsg->message == WM_LBUTTONDOWN) || (pMsg->message == WM_LBUTTONUP))
    {

        no_mouse_keyboard_event_enable_refresh = false;
        time_click = time(NULL);
    }
    if(pMsg->message == WM_KEYDOWN  )
    {
        if(((GetAsyncKeyState( VK_LCONTROL ) & 0x8000))&&(pMsg->wParam ==VK_F2))
        {
            //OnToolIsptoolforone();

            int ret = AfxMessageBox(_T("This will reset the device to the factory defaults\n are you sure'?"),MB_YESNO ,3);
            if ( ret == IDYES)
            {
                if (is_connect())
                {
                    write_one(g_tstat_id,16,143);
                }
                else
                {
                    AfxMessageBox(_T("Please Connect to the Device!"));
                }
            }
            else
            {
                return TRUE;
            }



            return 1;
        }
        if(((GetAsyncKeyState( VK_LCONTROL ) & 0x8000))&&(pMsg->wParam =='R'))
        {
            OnToolIsptoolforone();
            return 1;
        }
        if(pMsg->wParam == VK_F8)
        {
            ReFresh();
            return 1;
        }
        if(pMsg->wParam == VK_F3)
        {
            OnToolRefreshLeftTreee();
        }

        if(pMsg->wParam == VK_F2)
        {
            //OnToolErease();
            return 1;
        }
        /*if(pMsg->wParam == VK_RETURN)
        {
        EnterConnectToANode();
        return 1;
        }*/


    }


    return CFrameWndEx::PreTranslateMessage(pMsg);
}
void CMainFrame::ReFresh()
{
//	int i;
    if (!is_connect())
    {
        return;
    }
    register_critical_section.Lock();
    for(int i=0; i<12; i++) //Modify by Fance , tstat 6 has more register than 512;
    {
        Read_Multi(g_tstat_id,&multi_register_value[i*100],i*100,100);
    }
    register_critical_section.Unlock();
    //Modify by Fance
    //Use product_register_value  to change all the multi_register_value[] to multi_register_value
    //such as :
    //multi_register_value[101]  ----> product_register_value[MODBUS_TEMPRATURE_CHIP]
    //In order to make sure the program also run correctly , so create a new array to replace.
    //When all of the number like "101" has changed to MODBUS_TEMPRATURE_CHIP.
    //the multi_register_value then will by annul.
    memcpy_s(product_register_value,sizeof(product_register_value),multi_register_value,sizeof(multi_register_value));


}
BOOL CMainFrame::GetIPbyHostName(CString strHostName,CString& strIP)
{

    WSAData   wsdata;
    WORD wVersionRequested=MAKEWORD(2,0);
    int  err=WSAStartup(wVersionRequested,&wsdata);
    hostent     *pHostent=NULL   ;
//    const char   *addr;
//	char   hostName[255];

//pHostent   =   gethostbyname("www.google.com\0");
// sockaddr_in   sa;
// memcpy(&sa.sin_addr.s_addr,pHostent->h_addr_list[0],pHostent->h_length);
    pHostent   =   gethostbyname(CW2A(strHostName));
    if(pHostent==NULL)
        return   false;
    if(pHostent->h_addr_list==NULL)
        return   false;
    sockaddr_in   sa;
    memcpy(&sa.sin_addr.s_addr,pHostent->h_addr_list[0],pHostent->h_length);
    strIP.Format(_T("%d.%d.%d.%d"),sa.sin_addr.S_un.S_un_b.s_b1,sa.sin_addr.S_un.S_un_b.s_b2,sa.sin_addr.S_un.S_un_b.s_b3,sa.sin_addr.S_un.S_un_b.s_b4);
    WSACleanup();
    return TRUE;

}
void CMainFrame::OnToolErease()
{
    CEreaseDlg Dlg;
    Dlg.DoModal();

}
void CMainFrame::OnToolFresh()
{
    ReFresh();
}
void CMainFrame::OnToolRefreshLeftTreee()
{
    BeginWaitCursor();
    //RefreshTreeView();
    PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);
    EndWaitCursor();

}
#include "ScanDlg.h"
void CMainFrame::DoConnectToANode( const HTREEITEM& hTreeItem )
{
    CADO ado;
    ado.OnInitADOConn();

    m_strCfgFilePath = g_strExePth + c_strCfgFileName;
    m_cfgFileHandler.CreateConfigFile(m_strCfgFilePath);

    CString filename;
    CString flashmethod;
    CString id;
    CString comport;
    CString BD;
    CString ip;
    CString ipport;

    CString strTemp;
    CString subnote;
    CString subID;
    m_cfgFileHandler.ReadFromCfgFileForAll(
        filename,
        flashmethod,
        id,
        comport,
        BD,
        ip,
        ipport,
        subnote,
        subID
    );



    CString g_strT3000LogString;
    no_mouse_keyboard_event_enable_refresh = false;

    if(User_Login_Window != NULL)
    {
        if(User_Login_Window->IsWindowVisible())	//如果客户点击其他的 设备，之前还停留在 登入界面就先关掉登入界面，后面再判断要不要登入;
            User_Login_Window->ShowWindow(SW_HIDE);
    }
    if(ScreenEdit_Window != NULL)
    {
        if(ScreenEdit_Window->IsWindowVisible())
        {
            for (int i=0; i<SCREEN_HOTKEY_COUNT; i++)
            {
                UnregisterHotKey(ScreenEdit_Window->m_hWnd, m_screenHotKeyID[i]);
            }
            UnregisterHotKey(ScreenEdit_Window->m_hWnd,KEY_INSERT);
            ::PostMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
            ::PostMessage(ScreenEdit_Window->m_hWnd,WM_CLOSE,NULL,NULL);
        }
        ScreenEdit_Window->ShowWindow(SW_HIDE);
        ScreenEdit_Window = NULL;
    }

    MainFram_hwd = this->m_hWnd;
    //20120420
    CDialog_Progess* pDlg = new CDialog_Progess(this,1,100);
    //创建对话框窗口
    pDlg->Create(IDD_DIALOG10_Progress, this);

    //居中显示
    //pDlg->CenterWindow();
    //void MoveWindow( LPCRECT lpRect, BOOL bRepaint = TRUE );
    //pDlg->MoveWindow(100,100,500,1000);
    pDlg->ShowProgress(0,0);
    //显示对话框窗口
    g_llerrCount = g_llTxCount = g_llRxCount = 0;//click tree, clear all count;
    old_tx_count = persent_array_count = 0;
    //::SetWindowPos(pDlg->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    RECT RECT_SET1;
    GetClientRect(&RECT_SET1);
    pDlg->MoveWindow(RECT_SET1.left+400,RECT_SET1.bottom-19,RECT_SET1.right/2+20,20,1);
    pDlg->ShowWindow(SW_HIDE);
    //20120420
    float flagsoftwareversion;
    //HTREEITEM hSelItem=m_pTreeViewCrl->GetSelectedItem();
    HTREEITEM hSelItem=hTreeItem;
    int nCounts=m_product.size();
    tree_product product_Node;
    int nSelectID=-1;
    UINT nSelectSerialNumber;
    UINT nSerialNumber=0;
    for(UINT i=0; i<m_product.size(); i++)
    {
        if(hSelItem==m_product.at(i).product_item )
        {

            int Scan_Product_ID=m_product.at(i).product_class_id;
            g_strT3000LogString.Format(_T("Trying to connect to %s:%d"),GetProductName(m_product.at(i).product_class_id),m_product.at(i).serial_number);
            //write_T3000_log_file(g_strT3000LogString);
            CString* pstrInfo = new CString(g_strT3000LogString);
            ::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));

            int nID=-1;
            int nTRet=-1;
            //g_tstat_id=m_product.at(i).product_id;
            product_Node=m_product.at(i);
            selected_product_index = i;//记录目前选中的是哪一个 产品;用于后面自动更新firmware;
            selected_tree_item = hTreeItem;
            Statuspanel.Empty();
            if(product_Node.note_parent_serial_number == 0)
            {
                Statuspanel.Format(_T("%u"),product_Node.panel_number);
            }
            else
            {
                for (int z=0; z<m_product.size(); z++)
                {
                    if(product_Node.note_parent_serial_number == m_product.at(z).serial_number)
                    {
                        Statuspanel.Format(_T("%u-%u"),m_product.at(z).panel_number,product_Node.product_id);
                    }
                }
            }

            //if(1)//GSM  模块
            if((m_product.at(i).protocol != PROTOCOL_GSM) && (m_product.at(i).protocol != PROTOCOL_REMOTE_IP)&&(m_product.at(i).protocol!=MODBUS_RS485))
            {
                if(!m_product.at(i).BuildingInfo.strIp.IsEmpty())
                {

                    CScanDlg scandlg;

                    if (!scandlg.TestPing(m_product.at(i).BuildingInfo.strIp))
                    {
                        //去掉进度条
                        pDlg->ShowWindow(SW_HIDE);
                        if(pDlg)
                            delete pDlg;//20120220
                        pDlg = NULL;



                        //	if (!scandlg.CheckTheSameSubnet(m_product.at(i).BuildingInfo.strIp))
                        //	{
                        //		CString StrTips;
                        //		StrTips.Format(_T("The net device is not in the same subnet.\nDo you want to try to make them in the same subnet?"));
                        //		int ret = AfxMessageBox(StrTips,MB_YESNOCANCEL ,3);
                        //		if ( ret == IDYES)
                        //		{
                        //			scandlg.Set_IsScan(FALSE);
                        //			scandlg.SetNode(product_Node);
                        //			scandlg.DoModal();
                        //		}

                        //	}
                        //	else
                        //{
                        BOOL is_OK = FALSE;
                        //TroubleShoot(m_product.at(i));

                        if(m_product.at(i).status_last_time[0] == true)
                        {
                            //if(m_product.at(i).NetworkCard_Address.CompareNoCase(m_product.at(i).BuildingInfo.strIp))
                            if(CheckTheSameSubnet(m_product.at(i).NetworkCard_Address,m_product.at(i).BuildingInfo.strIp) == false)
                            {
                                CTroubleShootDlg dlg;
                                dlg.SetNode(m_product.at(i));
                                if (dlg.DoModal()==IDOK)
                                {

                                    is_OK=dlg.is_ok;
                                    // 								scandlg.Set_IsScan(FALSE);
                                    // 								scandlg.SetNode(product_Node);
                                    // 								scandlg.DoModal();
                                }
                            }
                            else
                            {
                                g_llTxCount ++;
                                g_llerrCount ++;
                                bac_select_device_online = false;
                                m_pTreeViewCrl->turn_item_image(hSelItem ,false);//Can't connect to the device , it will show disconnection;
                                m_product.at(i).status_last_time[0] = false;
                                m_product.at(i).status_last_time[1] = false;
                                m_product.at(i).status_last_time[2] = false;
                                m_product.at(i).status = false;
                                //MessageBox(_T("Device is offline!"));	//Ping 不通 ， 还在一个网段 ， 还显示在线; 其实不在线;

                                if (!m_pDialogInfo->IsWindowVisible())
                                {
                                    m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Device is offline!"));
                                    m_pDialogInfo->ShowWindow(SW_SHOW);
                                }
                                /*  while(m_pDialogInfo->IsWindowVisible()){
                                Sleep(50);
                                continue;
                                }*/
                                return;
                            }

                        }
                        else
                        {
                            g_llTxCount ++;
                            g_llerrCount ++;
                            bac_select_device_online = false;
                            m_pTreeViewCrl->turn_item_image(hSelItem ,false);//Can't connect to the device , it will show disconnection;
                            m_product.at(i).status_last_time[0] = false;
                            m_product.at(i).status_last_time[1] = false;
                            m_product.at(i).status_last_time[2] = false;
                            m_product.at(i).status = false;
                            //MessageBox(_T("Device is offline!"));
                            if (!m_pDialogInfo->IsWindowVisible())
                            {
                                m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Device is offline!"));
                                m_pDialogInfo->ShowWindow(SW_SHOW);
                            }
                            //                             while(m_pDialogInfo->IsWindowVisible()){
                            //                                 Sleep(50);
                            //                                 continue;
                            //                             }
                            return;
                        }
                        if (!is_OK)
                        {
                            CString strTitle;
                            strTitle.Format(_T("Can't connect to %s,Ping %s -> Noresponse"),m_product.at(i).BuildingInfo.strIp,m_product.at(i).BuildingInfo.strIp);
                            m_pTreeViewCrl->turn_item_image(hSelItem ,false);//Can't connect to the device , it will show disconnection;
                            m_product.at(i).status_last_time[0] = false;
                            m_product.at(i).status_last_time[1] = false;
                            m_product.at(i).status_last_time[2] = false;
                            m_product.at(i).status = false;
                            g_llTxCount ++;
                            g_llerrCount ++;
                            bac_select_device_online = false;
                            //MessageBox(strTitle);
                            if (!m_pDialogInfo->IsWindowVisible())
                            {
                                m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strTitle);
                                m_pDialogInfo->ShowWindow(SW_SHOW);
                            }
                            //                             while(m_pDialogInfo->IsWindowVisible()){
                            //                                 Sleep(50);
                            //                                 continue;
                            //                             }
                            return;
                        }
                        else
                        {
                            g_llTxCount ++;
                            g_llRxCount ++;
                            bac_select_device_online = true;
                            m_pTreeViewCrl->turn_item_image(hSelItem ,TRUE);//Can't connect to the device , it will show disconnection;
                            m_product.at(i).status_last_time[0] = TRUE;
                            m_product.at(i).status_last_time[1] = false;
                            m_product.at(i).status_last_time[2] = false;
                            m_product.at(i).status = false;

                        }




                        return;
                    }
                    else
                    {
                        ::PostMessage(MainFram_hwd,MY_RX_TX_COUNT,1,0);
                        CString IP=m_product.at(i).BuildingInfo.strIp;
                        int Port=m_product.at(i).ncomport;
                        SetCommunicationType(1);
                        if (!Open_Socket2(IP,Port))
                        {
                            g_llTxCount ++;
                            g_llerrCount ++;
                            bac_select_device_online = false;
                            // MessageBox(_T("Connect failed!Please try again!"));
                            if (!m_pDialogInfo->IsWindowVisible())
                            {
                                m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Connect failed!Please try again!"));
                                m_pDialogInfo->ShowWindow(SW_SHOW);
                            }
                            //                         while(m_pDialogInfo->IsWindowVisible()){
                            //                             Sleep(50);
                            //                             continue;
                            //                         }

                        }
                        else
                        {
                            close_com();
                        }
                    }

                }
            }


            g_serialNum = product_Node.serial_number;
            if((product_Node.product_class_id == PM_CM5) || (product_Node.product_class_id == PM_MINIPANEL))	//如果是CM5或者MINIPANEL 才有 bacnet协议;
            {
#if 1//Modbus Poll Config 
                m_nStyle=1;
                CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                CFileFind fFind;
                if(!fFind.FindFile(g_configfile_path))
                {
                    CString strInfo;
                    strInfo.Format(_T("%d"),1);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),product_Node.BuildingInfo.strIp,g_configfile_path);
                    strInfo.Format(_T("%d"),product_Node.ncomport);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }
                else
                {
                    CString strInfo;
                    strInfo.Format(_T("%d"),1);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Address"),product_Node.BuildingInfo.strIp,g_configfile_path);
                    strInfo.Format(_T("%d"),product_Node.ncomport);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("IP Port"),strInfo,g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);
                    WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);
                }

#endif

                SetPaneString(1,_T(""));
                if(product_Node.product_class_id == PM_CM5)
                    bacnet_device_type = PRODUCT_CM5;
                CString temp_csa;
                temp_csa =  product_Node.BuildingInfo.strComPort;
                temp_csa = temp_csa.Right(temp_csa.GetLength() - 3);
                g_bac_instance = m_product.at(i).object_instance;
                g_selected_serialnumber = m_product.at(i).serial_number;
                g_mac = m_product.at(i).panel_number;
                bac_gloab_panel = g_mac;
                g_gloab_bac_comport = m_product.at(i).ncomport;
                //g_gloab_bac_comport =_wtoi(temp_csa);
                //g_gloab_bac_comport = 1;
                //if(0)	//GSM
                if(m_product.at(i).protocol == PROTOCOL_GSM)
                {
                    if(!TCP_Server_Running)
                    {
                        if(pDlg)
                            delete pDlg;//20120220
                        pDlg = NULL;
                        MessageBox(_T("Trying to connect a device with GSM module ,Please start the server!\r\nMenu -> Miscellaneous -> Gsmconnection"),_T("Information"),MB_OK | MB_ICONINFORMATION);
                        return;
                    }
                    else
                    {
                        if(m_tcp_connect_info.size() == 0)
                        {
                            if(pDlg)
                                delete pDlg;//20120220
                            pDlg = NULL;
                            MessageBox(_T("This device does't connect to T3000 server yet."),_T("Information"),MB_OK | MB_ICONINFORMATION);
                            return;
                        }
                        else
                        {
                            int found_device = -1;
                            for (int z=0; z<m_tcp_connect_info.size(); z++)
                            {
                                if(m_tcp_connect_info.at(z).serialnumber == m_product.at(i).serial_number)
                                {
                                    found_device = z;
                                    break;
                                }
                            }
                            if(found_device>=0)	//发现 已经连接的设备;
                            {
                                bip_set_socket(m_tcp_connect_info.at(found_device).client_socket);
                                SEND_COMMAND_DELAY_TIME = 1000;
                            }
                            else
                            {
                                if(pDlg)
                                    delete pDlg;//20120220
                                pDlg = NULL;
                                MessageBox(_T("This device does't connect to T3000 server yet."),_T("Information"),MB_OK | MB_ICONINFORMATION);
                                return;
                            }

                        }

                    }

                }
                else if(m_product.at(i).protocol == MODBUS_BACNET_MSTP)
                {
                    g_protocol = MODBUS_BACNET_MSTP;
                    SEND_COMMAND_DELAY_TIME = 200;
                    SwitchToPruductType(DLG_BACNET_VIEW);

                    pDlg->ShowWindow(SW_HIDE);
                    if(pDlg)
                        delete pDlg;//20120220
                    pDlg = NULL;
                    m_pTreeViewCrl->SetSelectItem(hTreeItem);//在线的时候才将颜色变红;
                    m_pTreeViewCrl->SetSelectSerialNumber(product_Node.serial_number);
                    g_selected_serialnumber = m_product.at(i).serial_number;
                    return;

                }
                else
                {
                    SEND_COMMAND_DELAY_TIME = 100;
                    BOOL is_local = true;
                    if(product_Node.protocol == PROTOCOL_REMOTE_IP)
                        is_local = false;
                    //BOOL is_local = IP_is_Local(product_Node.BuildingInfo.strIp);
                    if(is_local == false)	//判断是否是本地IP，不是本地的就要连接到远端的，远端的 Who  is  广播发布过去的;
                    {
                        SEND_COMMAND_DELAY_TIME = 500;
                        m_is_remote_device = true;
                        ((CDialogCM5_BacNet*)m_pViews[m_nCurView])->Set_remote_device_IP(product_Node.BuildingInfo.strIp);
                        ((CDialogCM5_BacNet*)m_pViews[m_nCurView])->SetConnected_IP(product_Node.BuildingInfo.strIp);
                    }
                    else
                    {
                        m_is_remote_device = false;
                        ((CDialogCM5_BacNet*)m_pViews[m_nCurView])->SetConnected_IP(product_Node.BuildingInfo.strIp);
                    }
                }


#if 1 //ISPTool Config 
                /*	CString filename;
                CString flashmethod;
                CString id;
                CString comport;
                CString BD;
                CString ip;
                CString ipport;


                CString subnote;
                CString subID;*/
                //	id.Format(_T("%d"),)
                CString ProductHexBinName,StrTemp;
                CString StrBinHexPath,StrULRPath;
                GetProductFPTAndLocalPath(product_Node.product_class_id,StrULRPath,ProductHexBinName);
                StrBinHexPath = g_strExePth;
                StrBinHexPath+=_T("firmware\\");

                StrTemp.Format(_T("%s\\"),GetProductName(product_Node.product_class_id));
                StrBinHexPath+=StrTemp;
                StrBinHexPath+=ProductHexBinName;

                HANDLE hFind;//
                WIN32_FIND_DATA wfd;//
                hFind = FindFirstFile(StrBinHexPath, &wfd);//
                if ((hFind!=INVALID_HANDLE_VALUE)&&(!StrULRPath.IsEmpty()))//说明当前目录下无t3000.mdb
                {
                    filename=StrBinHexPath;
                }

                ip=product_Node.BuildingInfo.strIp;
                ipport=product_Node.BuildingInfo.strIpPort;
                m_cfgFileHandler.WriteToCfgFile(filename,
                                                _T("Ethernet"),
                                                id,
                                                comport,
                                                BD,
                                                ip,
                                                ipport,
                                                subnote,
                                                subID);

#endif
                //g_protocol = PROTOCOL_BACNET_IP;
                if(product_Node.protocol == PROTOCOL_BIP_TO_MSTP)
                    g_protocol = PROTOCOL_BIP_TO_MSTP;
                else
                    g_protocol =PROTOCOL_BACNET_IP;
                /*bac_net_initial_once = false;*/
                SwitchToPruductType(DLG_BACNET_VIEW);

                pDlg->ShowWindow(SW_HIDE);
                if(pDlg)
                    delete pDlg;//20120220
                pDlg = NULL;
                m_pTreeViewCrl->SetSelectItem(hTreeItem);//在线的时候才将颜色变红;
                m_pTreeViewCrl->SetSelectSerialNumber(product_Node.serial_number);
                g_selected_serialnumber = m_product.at(i).serial_number;
                g_bPauseMultiRead = true;
                return;
                //}
            }

            HANDLE temphandle;
            if(bac_net_initial_once)
            {
                temphandle = Get_RS485_Handle();
                if(temphandle !=NULL)
                {
                    TerminateThread((HANDLE)Get_Thread1(),0);
                    TerminateThread((HANDLE)Get_Thread2(),0);

                    CloseHandle(temphandle);
                    Set_RS485_Handle(NULL);
                    bac_net_initial_once = false;
                }
            }

            //************************************
            strTemp.Format(_T("\ng_tstat_id =%d   product_id =%d\n"),g_tstat_id,product_Node.product_id);
            TRACE(strTemp);
            if (g_tstat_id!=product_Node.product_id)
            {
                register_critical_section.Lock();
                g_tstat_id_changed=TRUE;
                strTemp.Format(_T("Lock\n"));
                //TRACE(strTemp);
                g_tstat_id=product_Node.product_id;
                register_critical_section.Unlock();
                strTemp.Format(_T("UnLock\n"));
                //TRACE(strTemp);
            }


            //***************************************
            strTemp.Format(_T("SelectID=%d\n"),product_Node.product_id);
            //TRACE(strTemp);
            nSelectID=product_Node.product_id;
            nSelectSerialNumber=product_Node.serial_number;
            flagsoftwareversion = product_Node.software_version;


            CString strTitle;
            strTitle=product_Node.BuildingInfo.strMainBuildingname;
            strTitle+=_T("->");
            strTitle+=product_Node.BuildingInfo.strBuildingName;

            m_wndWorkSpace.SetWindowText(strTitle);

            g_strImagePathName=product_Node.strImgPathName;
            if (!(
                        (product_Node.BuildingInfo.strIp.CompareNoCase(_T("9600")) ==0)	||
                        (product_Node.BuildingInfo.strIp.CompareNoCase(_T("19200"))==0) ||
                        (product_Node.BuildingInfo.strIp.CompareNoCase(_T("38400"))==0) ||
                        (product_Node.BuildingInfo.strIp.CompareNoCase(_T("57600"))==0) ||
                        (product_Node.BuildingInfo.strIp.CompareNoCase(_T(""))) == 0))
            {

                if(product_Node.BuildingInfo.hCommunication==NULL||m_strCurSubBuldingName.CompareNoCase(product_Node.BuildingInfo.strBuildingName)!=0)
                {
                    //pDlg->ShowProgress(2,10);//20120220
                    strTemp.Format(_T("Connect\n"));
                    TRACE(strTemp);
                    BOOL bRet = ConnectDevice(product_Node);//ConnectSubBuilding(product_Node.BuildingInfo);


                    SetLastCommunicationType(1);
//                     unsigned short read_data[10];
//
//                     strTemp.Format(_T("Begain Read\n"));
//                     TRACE(strTemp);
//                     g_bPauseMultiRead = TRUE;
//                     int nmultyRet=Read_Multi(g_tstat_id,&read_data[0],0,10,3);
//                     strTemp.Format(_T("nMultyRet=%d\n"),nmultyRet);
//                     TRACE(strTemp);
//
//                     if (nmultyRet>0)
//                     {
//                         ID1=read_data[6];
//                     }
//                     nmultyRet=Read_Multi(255,&read_data[0],0,10,3);
//
//                     strTemp.Format(_T("nMultyRet=%d\n"),nmultyRet);
//                     TRACE(strTemp);
//                     if (nmultyRet>0)
//                     {
//                         ID2=read_data[6];
//                     }

//ISPTool Config
#if 1
                    /*	CString filename;
                    CString flashmethod;
                    CString id;
                    CString comport;
                    CString BD;
                    CString ip;
                    CString ipport;
                    CString subnote;
                    CString subID;*/
                    //	id.Format(_T("%d"),)

                    /*ip=product_Node.BuildingInfo.strIp;
                    ipport=product_Node.BuildingInfo.strIpPort;
                    if (ID1!=ID2)
                    {
                      subID.Format(_T("%d"),g_tstat_id);
                      subnote.Format(_T("1"));
                    }*/

                    // CString ProductHexBinName,StrTemp;
                    // CString StrBinHexPath,StrULRPath;
                    // GetProductFPTAndLocalPath(product_Node.product_class_id,StrULRPath,ProductHexBinName);
                    // StrBinHexPath = g_strExePth;
                    //StrBinHexPath+=_T("firmware\\");

                    // StrTemp.Format(_T("%s\\"),GetProductName(product_Node.product_class_id));
                    //StrBinHexPath+=StrTemp;
                    // StrBinHexPath+=ProductHexBinName;

// 				 HANDLE hFind;//
// 				 WIN32_FIND_DATA wfd;//
// 				 hFind = FindFirstFile(StrBinHexPath, &wfd);//
// 				 if ((hFind!=INVALID_HANDLE_VALUE)&&(!StrULRPath.IsEmpty()))//说明当前目录下无t3000.mdb
// 				 {
// 					 filename=StrBinHexPath;
                    // }


                    m_cfgFileHandler.WriteToCfgFile(filename,
                                                    _T("Ethernet"),
                                                    id,
                                                    comport,
                                                    BD,
                                                    ip,
                                                    ipport,
                                                    subnote,
                                                    subID);

#endif
                }
            }
            //串口设置
            else
            {
                g_protocol=MODBUS_RS485;
// 				if (product_Node.BuildingInfo.strComPort.CompareNoCase(_T("N/A")) == 0)
// 				{
// 					AfxMessageBox(_T("Please select COM port"));//\nDatabase->Building config Database
// 					CAddBuilding  Dlg;
// 					if(Dlg.DoModal()==IDOK)
// 					{
// 					}
//
// 				}
// 				else
                {
                    //close_com();//关闭所有端口
                    //int nComPort = _wtoi(product_Node.BuildingInfo.strComPort.Mid(3));

                    int nComPort = product_Node.ncomport;
                    if(nComPort == 0 )
                    {
                        //nComPort = _wtoi(product_Node.BuildingInfo.strComPort.Mid(3));
                        // AfxMessageBox(_T("Comport is 0,Error"));
                        if (!m_pDialogInfo->IsWindowVisible())
                        {
                            m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Comport is 0,Error"));
                            m_pDialogInfo->ShowWindow(SW_SHOW);
                        }
//                          while(m_pDialogInfo->IsWindowVisible()){
//                              Sleep(50);
//                              continue;
//                          }
                        if (pDlg !=NULL)
                        {
                            pDlg->ShowWindow(SW_HIDE);
                            delete pDlg;
                            pDlg=NULL;
                        }
                        return;
                    }
                    //SetPaneCommunicationPrompt(strInfo);
                    SetCommunicationType(0);
                    if (is_connect())
                    {
                        close_com();
                    }
                    Sleep(1000);
                    BOOL  bret = open_com(nComPort);
                    if (!bret)	 //Try one more time
                    {
                        bret =	open_com(nComPort);
                    }
                    if (!bret)
                    {
                        strTemp.Format(_T("Open COM%d  Failed,Try again!"),nComPort);
                        //AfxMessageBox(strTemp);
                        if (!m_pDialogInfo->IsWindowVisible())
                        {
                            m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strTemp);
                            m_pDialogInfo->ShowWindow(SW_SHOW);
                        }
//                         while(m_pDialogInfo->IsWindowVisible()){
//                             Sleep(50);
//                             continue;
//                         }
                        if (pDlg !=NULL)
                        {
                            pDlg->ShowWindow(SW_HIDE);
                            delete pDlg;
                            pDlg=NULL;
                        }
                        m_nStyle=2;
                        return;
                    }
                    else
                    {
                        CString strInfo;
                        strInfo.Format(_T("COM %d Connected: Yes"), nComPort);
                        SetPaneString(1, strInfo);
                        SetCommunicationType(0);
                        g_CommunicationType=0;

                        m_nStyle=1;

                        CString	g_configfile_path=g_strExePth+_T("T3000_config.ini");
                        CFileFind fFind;
                        if(!fFind.FindFile(g_configfile_path))
                        {
                            CString strInfo;
                            strInfo.Format(_T("%d"),g_CommunicationType);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
                            strInfo.Format(_T("COM%d"),nComPort);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
                            strInfo.Format(_T("%d"),nComPort);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);
                            strInfo.Format(_T("%d"),product_Node.baudrate);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);


                            /*	WritePrivateProfileStringW(_T("Setting"),_T("IP Address"),StringIP,g_configfile_path);
                            	strInfo.Format(_T("%d"),m_nIpPort);
                            	WritePrivateProfileStringW(_T("Setting"),_T("IP Port"),strInfo,g_configfile_path);

                            	WritePrivateProfileStringW(_T("Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                            	WritePrivateProfileStringW(_T("Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);

                            	WritePrivateProfileStringW(_T("Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);*/
                        }
                        else
                        {
                            CString strInfo;
                            strInfo.Format(_T("%d"),g_CommunicationType);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Connection Type"),strInfo,g_configfile_path);
                            strInfo.Format(_T("COM%d"),nComPort);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM Port"),strInfo,g_configfile_path);
                            strInfo.Format(_T("%d"),nComPort);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("COM_Port"),strInfo,g_configfile_path);
                            strInfo.Format(_T("%d"),product_Node.baudrate);
                            WritePrivateProfileStringW(_T("MBPOLL_Setting"),_T("Baudrate"),strInfo,g_configfile_path);

                            /*WritePrivateProfileStringW(_T("Setting"),_T("IP Address"),_T("127.0.0.1"),g_configfile_path);
                            strInfo.Format(_T("%d"),m_nIpPort);
                            WritePrivateProfileStringW(_T("Setting"),_T("IP Port"),strInfo,g_configfile_path);
                            WritePrivateProfileStringW(_T("Setting"),_T("Response Timeout"),_T("1000"),g_configfile_path);
                            WritePrivateProfileStringW(_T("Setting"),_T("Delay Between Time"),_T("1000"),g_configfile_path);
                            WritePrivateProfileStringW(_T("Setting"),_T("Connect Timeout"),_T("3000"),g_configfile_path);*/
                        }





#if 1
                        //ISPTool Config
                        /*	CString filename;
                        CString flashmethod;
                        CString id;
                        CString comport;
                        CString BD;
                        CString ip;
                        CString ipport;


                        CString subnote;
                        CString subID;*/


                        //CString ProductHexBinName,StrTemp;
                        //CString StrBinHexPath,StrULRPath;
                        //GetProductFPTAndLocalPath(product_Node.product_class_id,StrULRPath,ProductHexBinName);
                        //StrBinHexPath = g_strExePth;
                        //StrBinHexPath+=_T("firmware\\");

                        //StrTemp.Format(_T("%s\\"),GetProductName(product_Node.product_class_id));
                        //StrBinHexPath+=StrTemp;
                        //StrBinHexPath+=ProductHexBinName;

                        //HANDLE hFind;//
                        //WIN32_FIND_DATA wfd;//
                        //hFind = FindFirstFile(StrBinHexPath, &wfd);//
                        //if ((hFind!=INVALID_HANDLE_VALUE)&&(!StrULRPath.IsEmpty()))//说明当前目录下无t3000.mdb
                        //{
                        //	filename=StrBinHexPath;
                        //}


                        id.Format(_T("%d"),g_tstat_id);
                        comport.Format(_T("COM%d"),nComPort);
                        BD.Format(_T("%d"),product_Node.baudrate);
                        ip=product_Node.BuildingInfo.strIp;
                        ipport=product_Node.BuildingInfo.strIpPort;
                        m_cfgFileHandler.WriteToCfgFile(filename,
                                                        _T("COM"),
                                                        id,
                                                        comport,
                                                        BD,
                                                        ip,
                                                        ipport,
                                                        subnote,
                                                        subID);
#endif
                    }
                }
            }

            m_strCurSubBuldingName=product_Node.BuildingInfo.strBuildingName;
            BOOL bOnLine=FALSE;
            UINT nSerialNumber=0;
            int Device_Type = 0;
            unsigned short read_data[10];
            if (g_CommunicationType==0)
            {
                //m_nbaudrat=_wtoi(product_Node.BuildingInfo.strBaudRate);
                g_protocol=MODBUS_RS485;
                m_nbaudrat= product_Node.baudrate;
                if ((m_nbaudrat !=9600 ) && (m_nbaudrat !=19200) && (m_nbaudrat != 38400)&& (m_nbaudrat != 57600))
                    m_nbaudrat = 19200;
                Change_BaudRate(m_nbaudrat);


                register_critical_section.Lock();
                int nmultyRet=Read_Multi(g_tstat_id,&read_data[0],0,10,3);
                register_critical_section.Unlock();
                if(nmultyRet <0)
                {
                    //AfxMessageBox(_T("Your comport is open ,but T3000 can't read your device."));//\nDatabase->Building config Database
                    if (!m_pDialogInfo->IsWindowVisible())
                    {
                        m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Your comport is open ,but maybe your device is offline!"));
                        m_pDialogInfo->ShowWindow(SW_SHOW);
                    }
//                     while(m_pDialogInfo->IsWindowVisible()){
//                         Sleep(50);
//                         continue;
//                     }
                    if (pDlg !=NULL)
                    {
                        pDlg->ShowWindow(SW_HIDE);
                        delete pDlg;
                        pDlg=NULL;
                    }
                    bOnLine=FALSE;
                    m_pTreeViewCrl->turn_item_image(hSelItem ,false);
                    m_product.at(i).status_last_time[0] = false;
                    m_product.at(i).status_last_time[1] = false;
                    m_product.at(i).status_last_time[2] = false;
                    return;
                }
                else
                {
                    SetLastSuccessBaudrate(m_nbaudrat);

                    m_pTreeViewCrl->SetSelectItem(hTreeItem);//在线的时候才将颜色变红;
                    m_pTreeViewCrl->SetSelectSerialNumber(product_Node.serial_number);
                    g_selected_serialnumber = m_product.at(i).serial_number;


                    nSerialNumber=read_data[0]+read_data[1]*256+read_data[2]*256*256+read_data[3]*256*256*256;
                    Device_Type = read_data[7];
                    if(nSerialNumber>=0)
                    {
                        //	if(nSerialNumber==nSelectSerialNumber)
                        //{
                        SetLastOpenedComport(product_Node.ncomport);
                        SetLastCommunicationType(0);
                        bOnLine=TRUE;

                        CString temp_value = m_subNetLst.at(0).strComPort;
                        if(temp_value.GetLength() > 3)
                        {
                            CString cs_temp_1;
                            cs_temp_1 = temp_value.Right(temp_value.GetLength() - 3);
                            int i_temp_port = _wtoi(cs_temp_1);
                            if(i_temp_port != product_Node.ncomport)
                            {
                                CString temp_cs_port;
                                temp_cs_port.Format(_T("COM%u"),product_Node.ncomport);
                                try
                                {

                                    CString strSql;

                                    strSql.Format(_T("update Building set Com_Port='%s' where Building_Name='%s' and Main_BuildingName='%s'"),temp_cs_port,m_strCurSubBuldingName,m_strCurMainBuildingName);
                                    //m_pRs->Open((_variant_t)strSql,_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);

                                    ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);


                                    m_subNetLst.at(0).strComPort = temp_cs_port;
                                }
                                catch (...)
                                {

                                }
                            }
                        }

                        //}
// 						else
// 						{
// 							CString tempcs;
// 							tempcs.Format(_T("The device serial number is %d,the database saved is %d \r\nPlease delete it and rescan."),nSerialNumber,nSelectSerialNumber);
// 							MessageBox(tempcs);
// 						}
                    }
                }
            }
            if (g_CommunicationType==1)
            {
                SetLastCommunicationType(1);
                g_protocol=MODBUS_TCPIP;
                // SetResponseTime (2000);   For Kaiyin's TstatHUM
                int nmultyRet=Read_Multi(g_tstat_id,&read_data[0],0,10,5);

                //
                if(nmultyRet <0)
                {
                    //AfxMessageBox(_T("Device is offline,Please check the connection!"));//\nDatabase->Building config Database
                    if (!m_pDialogInfo->IsWindowVisible())
                    {
                        m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Device is offline,Please check the connection!"));
                        m_pDialogInfo->ShowWindow(SW_SHOW);
                    }
//                     while(m_pDialogInfo->IsWindowVisible()){
//                         Sleep(50);
//                         continue;
//                     }
                    if (pDlg !=NULL)
                    {
                        pDlg->ShowWindow(SW_HIDE);
                        delete pDlg;
                        pDlg=NULL;
                    }
                    bOnLine=FALSE;
                }
                else
                {
                    UINT nSerialNumber=0;

                    nSerialNumber=read_data[0]+read_data[1]*256+read_data[2]*256*256+read_data[3]*256*256*256;
                    Device_Type = read_data[7];
                    CString Temp_product_name = GetProductName(Device_Type);
                    if(Temp_product_name.IsEmpty())
                    {
                        CString tempcs;
                        tempcs.Format(_T("Product ID is invalid .Product id is %d \r\n"),Device_Type);
                        if (!m_pDialogInfo->IsWindowVisible())
                        {
                            m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(tempcs);
                            m_pDialogInfo->ShowWindow(SW_SHOW);
                        }
//                         while(m_pDialogInfo->IsWindowVisible()){
//                             Sleep(50);
//                             continue;
//                         }
                        if (pDlg !=NULL)
                        {
                            pDlg->ShowWindow(SW_HIDE);
                            delete pDlg;
                            pDlg=NULL;
                        }
                        //MessageBox(tempcs);

                        return;

                    }
                    if(nSerialNumber>=0)
                    {
//if(nSerialNumber==nSelectSerialNumber)
                        bOnLine=TRUE;
// 						else
// 						{
// 							CString tempcs;
// 							tempcs.Format(_T("The device serial number is %d,the database saved is %d \r\nPlease delete it and rescan."),nSerialNumber,nSelectSerialNumber);
// 							MessageBox(tempcs);
// 						}
                    }
                }
            }

            if(bOnLine)
            {
                //SetPaneConnectionPrompt(_T("Online!"));
                pDlg->ShowWindow(SW_HIDE);
                m_pTreeViewCrl->SetSelectItem(hTreeItem);//在线的时候才将颜色变红;
                m_pTreeViewCrl->SetSelectSerialNumber(product_Node.serial_number);
                g_selected_serialnumber = m_product.at(i).serial_number;
                m_pTreeViewCrl->turn_item_image(hSelItem ,true);
                m_nStyle=1;
            }
            else
            {

                //SetPaneConnectionPrompt(_T("Offline!"));
                m_pTreeViewCrl->turn_item_image(hSelItem ,false);
                memset(&multi_register_value[0],0,sizeof(multi_register_value));
                m_nStyle=2;
                m_product.at(i).status_last_time[0] = false;
                m_product.at(i).status_last_time[1] = false;
                m_product.at(i).status_last_time[2] = false;
                //20120424
                if (pDlg !=NULL)
                {
                    pDlg->ShowWindow(SW_HIDE);
                    delete pDlg;
                    pDlg=NULL;
                }
                return;
            }
            /*
            Comment by:Alex
            Date:2013/04/10
            Purpose:
            这个的目的的当是通过TCP连接的时候，把读到的寄存器读到
            multi_register_value_tcp
            适用于网络口，大数据量
            */
            //Device_Type=read_one(g_tstat_id,7,10);
            CString achive_file_path;
            CString temp_serial;
            temp_serial.Format(_T("%u.prg"),g_selected_serialnumber);
            if (Device_Type == 0)
            {
                Device_Type=Scan_Product_ID;
            }
            achive_file_path = g_achive_folder + _T("\\") + temp_serial;
            if(/*Load_Product_Value_Cache(achive_file_path) < 0*/1 )
            {
                if (Device_Type==100)
                {

                    register_critical_section.Lock();
                    int i;
                    int it = 0;
                    float progress;
                    for(i=0; i<12; i++)
                    {
                        //register_critical_section.Lock();
                        //int nStart = GetTickCount();
                        int itemp = 0;
                        itemp = Read_Multi(g_tstat_id,&multi_register_value[i*100],i*100,100,3);
                        if(itemp < 0 )
                        {
                            //continue;
                            break; //读不到就退出，很多时候 NC在读的过程中断开连接T3000 还一直去读剩余的 就会引起无响应;
                        }
                        else
                        {
                            if (pDlg!=NULL)
                            {
                                progress=float((it+1)*(100/12));
                                //pDlg->ShowProgress(int(progress),(int)progress);
                                g_progress_persent = progress;
                            }
                        }
                        it++;
                        Sleep(100);
                    }


                    if (it<12)
                    {
                        //AfxMessageBox(_T("Reading abnormal \n Try again!"));
                        if (!m_pDialogInfo->IsWindowVisible())
                        {
                            m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Reading abnormal \n Try again!"));
                            m_pDialogInfo->ShowWindow(SW_SHOW);
                        }
//                     while(m_pDialogInfo->IsWindowVisible()){
//                         Sleep(50);
//                         continue;
//                     }

                        pDlg->ShowWindow(SW_HIDE);
                        if(pDlg!=NULL)
                            delete pDlg;
                        pDlg=NULL;

                    }
                    else
                    {
                        pDlg->ShowProgress(100,100);
                        pDlg->ShowWindow(SW_HIDE);
                        if(pDlg!=NULL)
                            delete pDlg;
                        pDlg=NULL;
                    }
                    g_tstat_id_changed=FALSE;
                    register_critical_section.Unlock();
                }
                else if(Device_Type > 0)
                {
                    int Use_zigee = 0;
                    int power_value = 1;
                    int length = 10;
                    nFlag = Device_Type;
                    int it = 0;
                    if((nFlag == PM_TSTAT6) || (nFlag == PM_TSTAT7)|| (nFlag == PM_TSTAT5i) || (nFlag == PM_TSTAT8))
                    {
                        product_type =T3000_6_ADDRESS;
                    }
                    else if((nFlag == PM_TSTATRUNAR)||(nFlag == PM_TSTAT5E||nFlag == PM_PM5E) || (nFlag == PM_TSTAT5H)||(nFlag==PM_TSTAT5G))
                    {
                        product_type = T3000_5EH_LCD_ADDRESS;
                    }
                    else if((nFlag == PM_TSTAT5A) ||(nFlag == PM_TSTAT5B) ||
                            (nFlag ==PM_TSTAT5C ) || (nFlag == PM_TSTAT5D) || (nFlag == PM_TSTAT5F))
                    {
                        product_type =T3000_5ABCDFG_LED_ADDRESS;
                    }
                    else if (nFlag==PM_CS_SM_AC||nFlag==PM_CS_SM_DC||nFlag==PM_CS_RSM_AC||nFlag==PM_CS_RSM_DC)
                    {
                        product_type=CS3000;
                    }
                    else if (nFlag==PM_T3PT10||nFlag==PM_T3IOA||nFlag==PM_T332AI||nFlag== PM_T38AI16O||nFlag==PM_T38I13O||
                             nFlag==PM_T34AO||nFlag==PM_T36CT||nFlag==PM_T3PERFORMANCE||
                             nFlag == PM_T322AI||
                             nFlag == PM_T38AI8AO6DO)
                    {
                        product_type=T3000_T3_MODULES;
                    }
                    else
                    {
                        product_type=nFlag;
                    }




                    memset(&multi_register_value[0],0,sizeof(multi_register_value));

                    if(product_type == T3000_6_ADDRESS)
                    {
                        power_value = 1;
                        register_critical_section.Lock();
                        int i;
                        it =0;
                        float progress;
                        for(i=0; i<(length*power_value); i++)	//暂定为0 ，因为TSTAT6 目前为600多
                        {
                            int itemp = 0;
                            itemp = Read_Multi(g_tstat_id,&multi_register_value[i*(100/power_value)],i*(100/power_value),100/power_value,5);
                            if(itemp < 0)
                            {
                                break;
                            }
                            else
                            {
                                if (pDlg!=NULL)
                                {
                                    progress=float((it+1)*(100/(9*power_value)));
                                    //pDlg->ShowProgress(int(progress),int(progress));
                                    g_progress_persent = progress;
                                }
                            }
                            it++;
                            Sleep(20 * power_value);
                        }
                        g_tstat_id_changed=FALSE;
                        register_critical_section.Unlock();

                    }
                    else if (product_type == T3000_T3_MODULES)
                    {
                        length =4;
                        power_value = 1;
                        register_critical_section.Lock();
                        int i;
                        it =0;
                        float progress;
                        for(i=0; i<(length*power_value); i++)	//暂定为0 ，因为TSTAT6 目前为600多
                        {
                            int itemp = 0;
                            itemp = Read_Multi(g_tstat_id,&multi_register_value[i*(100/power_value)],i*(100/power_value),100/power_value,5);
                            if(itemp < 0)
                            {
                                break;
                            }
                            else
                            {
                                if (pDlg!=NULL)
                                {
                                    progress=float((it+1)*(100/(length*power_value)));
                                    //pDlg->ShowProgress(int(progress),int(progress));
                                    g_progress_persent = progress;
                                }
                            }
                            it++;
                            Sleep(20 * power_value);
                        }
                        g_tstat_id_changed=FALSE;
                        register_critical_section.Unlock();
                    }
                    else
                    {
                        power_value = 1;
                        length = 9;
                        register_critical_section.Lock();
                        int i;
                        float progress;
                        for(i=0; i<(length*power_value); i++)	//暂定为0 ，因为TSTAT6 目前为600多
                        {
                            int itemp = 0;
                            itemp = Read_Multi(g_tstat_id,&multi_register_value[i*(100/power_value)],i*(100/power_value),100/power_value,5);
                            if(itemp < 0)
                            {
                                break;
                            }
                            else
                            {
                                if (pDlg!=NULL)
                                {
                                    progress=float((it+1)*(100/(9*power_value)));
                                    //pDlg->ShowProgress(int(progress),int(progress));
                                    g_progress_persent = progress;
                                }
                            }
                            it++;
                            Sleep(20 * power_value);
                        }
                        g_tstat_id_changed=FALSE;
                        register_critical_section.Unlock();
                    }


                    memcpy_s(product_register_value,sizeof(product_register_value),multi_register_value,sizeof(multi_register_value));


                    if ((nFlag == PM_TSTAT6||nFlag == PM_TSTAT7||nFlag == PM_HUMTEMPSENSOR||nFlag ==PM_AirQuality||nFlag ==PM_HUM_R) && product_register_value[714] == 0x56)
                    {
                        CString TstatName,TstatDBName;

                        CBADO bado;
                        bado.SetDBPath(g_strCurBuildingDatabasefilePath);
                        bado.OnInitADOConn();
                        CString strSerial;
                        strSerial.Format(_T("%d"),get_serialnumber());

#if 1 // 点击的时候把新的Tstat6的名字写到Tstat6的寄存器中
                        CString temp_serial_number;
                        CString newname;
                        CString strSql;



                        temp_serial_number.Format(_T("%u"),g_selected_serialnumber);

                        int temp_write_flag = GetPrivateProfileInt(temp_serial_number,_T("WriteFlag"),0,g_achive_device_name_path);
                        if (temp_write_flag == 1)
                        {
                            GetPrivateProfileStringW(temp_serial_number,_T("NewName"),_T(""),newname.GetBuffer(MAX_PATH),MAX_PATH,g_achive_device_name_path);
                            if(newname.GetLength()> 16)	//长度不能大于结构体定义的长度;
                            {
                                newname.Delete(16,newname.GetLength()-16);
                            }
                            char cTemp1[16];
                            memset(cTemp1,0,16);
                            WideCharToMultiByte( CP_ACP, 0, newname.GetBuffer(), -1, cTemp1, 16, NULL, NULL );
                            unsigned char Databuffer[16];
                            memcpy_s(Databuffer,16,cTemp1,16);
                            if (Write_Multi(g_tstat_id,Databuffer,715,16,3)>0)
                            {
                                for (int i=0; i<16; i++)
                                {
                                    product_register_value[715+i]=Databuffer[i];
                                }




                                strSql.Format(_T("update ALL_NODE set Product_name='%s' where Serial_ID='%s'"),newname,strSerial);
                                bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);

                                WritePrivateProfileStringW(temp_serial_number,_T("WriteFlag"),L"0",g_achive_device_name_path);
                                PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);
                            }
                        }


                        strSql.Format(_T("select * from  ALL_NODE  where Serial_ID='%s'"),strSerial);
                        bado.m_pRecordset = bado.OpenRecordset(strSql);
                        if (!bado.m_pRecordset->EndOfFile)
                        {
                            TstatDBName = bado.m_pRecordset->GetCollect(_T("Product_name"));
                        }
                        bado.CloseRecordset();
                        TstatName.Format(_T("%s%s"),GetTextFromReg(715),GetTextFromReg(719));
                        if (TstatName.CompareNoCase(TstatDBName)!=0)
                        {
                            strSql.Format(_T("update ALL_NODE set Product_name='%s' where Serial_ID='%s'"),TstatName,strSerial);
                            bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
                            PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);
                        }
                        bado.CloseConn();
#endif
                    }

                    //Code and comments by Fance
                    //Use old_product_type to save the last value.
                    //if this value is change ,it will reload the register value.
                    //example:
                    //For tstats 5A : product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 185
                    //For tstats 6	  product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 110
                    if(old_product_type!=product_type)
                    {
                        old_product_type = product_type;
                        MyRegAddress.Change_Register_Table();
                    }



                    GetIONanme();
                    if (product_type==T3000_6_ADDRESS)
                    {
                        LoadTstat_InputData();
                        LoadTstat_OutputData();
                    }
                    //int const PM_CO2_NET = 32;
                    // int const PM_CO2_RS485 = 33;
                    else if (product_type==CS3000)
                    {
                        LoadInputData_CS3000();
                        LoadOutputData_CS3000();
                    }

                    else if (product_type == T3000_T3_MODULES)
                    {


                    }
                    /*bac_net_initial_once = false;*/

                    if (it<length)
                    {
                        //AfxMessageBox(_T("Reading abnormal \n Try again!"));
                        if (!m_pDialogInfo->IsWindowVisible())
                        {
                            m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Reading abnormal \n Try again!"));
                            m_pDialogInfo->ShowWindow(SW_SHOW);
                        }
//                     while(m_pDialogInfo->IsWindowVisible()){
//                         Sleep(50);
//                         continue;
//                     }
                        pDlg->ShowWindow(SW_HIDE);
                        if(pDlg!=NULL)
                            delete pDlg;
                        pDlg=NULL;


                    }
                    else
                    {

                        pDlg->ShowProgress(100,100);
                        pDlg->ShowWindow(SW_HIDE);
                        if(pDlg!=NULL)
                            delete pDlg;
                        pDlg=NULL;
                    }

                }
                Save_Product_Value_Cache(achive_file_path);
            }
            else
            {
                pDlg->ShowProgress(100,100);
                pDlg->ShowWindow(SW_HIDE);
                if(pDlg!=NULL)
                    delete pDlg;
                pDlg=NULL;
            }

            g_serialNum=nSerialNumber;//get_serialnumber();
#if 1
            if(g_bPrivilegeMannage)
            {
                if(g_buser_log_in)
                {
                    if(g_strLoginUserName.CompareNoCase(_T("admin"))==0)
                    {
                        g_MainScreenLevel=0;
                        g_ParamLevel=0;
                        g_OutPutLevel=0;
                        g_NetWorkLevel=0;
                        g_GraphicModelevel=0;
                        g_BurnHexLevel=0;
                        g_LoadConfigLevel=0;
                        g_BuildingsetLevel=0;
                        g_AllscreensetLevel=0;
                    }
                    else
                    {
                        try
                        {



                            CString strSerial;
                            strSerial.Format(_T("%d"),g_serialNum);
                            strSerial.Trim();
                            CString strsql;
                            strsql.Format(_T("select * from user_level where MainBuilding_Name='%s' and Building_Name='%s' and username = '%s' and serial_number = %d"),m_strCurMainBuildingName,m_strCurSubBuldingName,g_strLoginUserName,g_serialNum);
                            ado.m_pRecordset=ado.OpenRecordset(strsql);

                            if(VARIANT_FALSE==ado.m_pRecordset->EndOfFile)
                            {
                                //获取权限：
                                g_AllscreensetLevel=ado.m_pRecordset->GetCollect("allscreen_level");
                                if(g_AllscreensetLevel!=1)
                                {
                                    g_MainScreenLevel=ado.m_pRecordset->GetCollect("mainscreen_level");//
                                    g_ParamLevel=ado.m_pRecordset->GetCollect("parameter_level");
                                    g_OutPutLevel=ado.m_pRecordset->GetCollect("outputtable_level");
                                    g_NetWorkLevel=ado.m_pRecordset->GetCollect("networkcontrol_level");//
                                    g_GraphicModelevel=ado.m_pRecordset->GetCollect("graphic_level");//
                                    g_BurnHexLevel=ado.m_pRecordset->GetCollect("burnhex_level");
                                    g_LoadConfigLevel=ado.m_pRecordset->GetCollect("loadconfig_level");
                                    g_BuildingsetLevel=ado.m_pRecordset->GetCollect("building_level");
                                }
                                else
                                {
                                    g_MainScreenLevel=1;
                                    g_ParamLevel=1;
                                    g_OutPutLevel=1;
                                    g_NetWorkLevel=1;
                                    g_GraphicModelevel=1;
                                    g_BurnHexLevel=1;
                                    g_LoadConfigLevel=1;
                                    g_BuildingsetLevel=1;
                                    g_AllscreensetLevel=1;

                                }



                            }

                            ado.CloseRecordset();



                            strSerial.Format(_T("%d"),g_serialNum);
                            strSerial.Trim();

                            strsql.Format(_T("select * from UserLevelSingleSet where MainBuilding_Name='%s' and Building_Name='%s' and username = '%s'"),m_strCurMainBuildingName,m_strCurSubBuldingName,g_strLoginUserName);
                            ado.m_pRecordset=ado.OpenRecordset(strsql);
                            if(VARIANT_FALSE==ado.m_pRecordset->EndOfFile)
                            {
                                //获取权限：
                                g_NetWorkLevel=ado.m_pRecordset->GetCollect("networkcontroller");//
                                g_BuildingsetLevel=ado.m_pRecordset->GetCollect("database_limition");
                            }

                            ado.CloseRecordset();



                        }
                        catch (...)
                        {
                        }
                    }

                }

            }




#endif
            nFlag = Device_Type;
            if(nFlag >65530)
            {

                //AfxMessageBox(_T("Reading product model abnormal \n Try again!"));
                if (!m_pDialogInfo->IsWindowVisible())
                {
                    m_pDialogInfo->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(_T("Reading abnormal \n Try again!"));
                    m_pDialogInfo->ShowWindow(SW_SHOW);
                }
//                 while(m_pDialogInfo->IsWindowVisible()){
//                     Sleep(50);
//                     continue;
//                 }
                if (pDlg !=NULL)
                {
                    pDlg->ShowWindow(SW_HIDE);
                    delete pDlg;
                    pDlg=NULL;
                }
                return;
            }
            //------------------------------------------------------------------
            g_HumChamberThread=FALSE;
            /* if (nFlag==PM_HUMTEMPSENSOR)
            {
            SwitchToPruductType(DLG_DIALOG_TEMP_HUMSENSOR);
            }*/
            if(nFlag==PM_NC)
            {
                SwitchToPruductType(DLG_NETWORKCONTROL_VIEW);
            }
            else if (nFlag == PM_CM5)//CM5
            {
                SwitchToPruductType(DLG_DIALOGCM5_VIEW);
            }
            else if (nFlag == PM_T3IOA)
            {

                SwitchToPruductType(DLG_DIALOGT38AI8AO);
            }
            else if (nFlag== PM_T38I13O)
            {

                SwitchToPruductType(DLG_DIALOGT38I13O_VIEW);
            }
            else if (nFlag == PM_T34AO) //T3
            {
                SwitchToPruductType(DLG_DIALOGT3_VIEW);
            }
            else if (nFlag== PM_T3PT10)
            {
                SwitchToPruductType(DLG_DIALOGT3PT10);
            }
            else if (nFlag==PM_T332AI)
            {
                SwitchToPruductType(DLG_DIALOGT332AI_VIEW);
            }
            else if (m_product.at(i).product_class_id==PM_T36CT)
            {
                SwitchToPruductType(DLG_DIALOGT36CT);
            }
            else if (nFlag==PM_T38I13O)
            {
                SwitchToPruductType(DLG_DIALOGT38I13O_VIEW);
            }
            else if (nFlag==PM_T332AI)
            {
                SwitchToPruductType(DLG_DIALOGT332AI_VIEW);
            }
            else if (nFlag==PM_T3IOA)
            {
                SwitchToPruductType(DLG_DIALOGT38AI8AO);
            }
            else if (nFlag == PM_MINIPANEL)
            {
                SwitchToPruductType(DLG_DIALOGMINIPANEL_VIEW);
            }
            else if (nFlag==PM_TSTAT6_HUM_Chamber)
            {
                g_HumChamberThread=TRUE;
                SwitchToPruductType(DLG_HUMCHAMBER);
            }
            else if(nFlag == PM_CO2_RS485||nFlag == PM_PRESSURE_SENSOR||nFlag == PM_CO2_NODE)//(nFlag == PM_CO2_NET)||
            {
                SwitchToPruductType(DLG_CO2_VIEW);
            }
            else if(nFlag == PM_CO2_NET)//(nFlag == PM_CO2_NET)||
            {
                SwitchToPruductType(DLG_CO2_NET_VIEW);
            }

            else if (nFlag==PM_PRESSURE)
            {
                SwitchToPruductType(DLG_DIALOG_PRESSURE_SENSOR);
            }
            else if (nFlag==PM_AirQuality||nFlag==PM_HUM_R||nFlag==PM_HUMTEMPSENSOR)
            {
                SwitchToPruductType(DLG_AIRQUALITY_VIEW);
            }
            else if (nFlag==PM_TSTAT6||nFlag==PM_TSTAT7||nFlag==PM_TSTAT5i||nFlag==PM_TSTAT8)
            {

                CString g_configfile_path =g_strExePth + g_strStartInterface_config;
                int m_lastinterface=GetPrivateProfileInt(_T("T3000_START"),_T("Interface"),19,g_configfile_path);
                if (DLG_T3000_VIEW!= m_lastinterface&&DLG_DIALOG_TSTAT_INPUT_VIEW!=m_lastinterface&&DLG_DIALOG_TSTAT_OUTPUT_VIEW!=m_lastinterface)
                {
                    m_lastinterface=DLG_T3000_VIEW ;
                }


                SwitchToPruductType(m_lastinterface);
            }
            else if (nFlag==PM_CS_SM_AC||nFlag==PM_CS_SM_DC||nFlag==PM_CS_RSM_AC||nFlag==PM_CS_RSM_DC)
            {

                SwitchToPruductType(DLG_DIALOG_TSTAT_INPUT_VIEW);
            }
            else if (nFlag == PM_T322AI || nFlag == CS3000 || nFlag == PM_T38AI8AO6DO)
            {
                bacnet_view_number = TYPE_TSTAT;
                SwitchToPruductType(DLG_DIALOG_DEFAULT_T3000_VIEW);
            }
            else if(nFlag<PM_NC)
            {

                //Use product_type to change the address map
                //if product module is TSTAT6 or TSTAT7 use T3000_6_ADDRESS. T3000_6_ADDRESS is a register table in t3000.mdb  T3000_Register_Address_By_Name
                //else if product module is PM_TSTAT5E PM_TSTAT5H use T3000_5EH_LCD_ADDRESS
                //else if product module is TSTAT5 ABCDFG USE T3000_5ABCDFG_LED_ADDRESS
                if((nFlag == PM_TSTAT6) || (nFlag == PM_TSTAT7)|| (nFlag == PM_TSTAT5i) || (nFlag == PM_TSTAT8))
                {
                    product_type = T3000_6_ADDRESS;
                }
                else if((nFlag == PM_TSTATRUNAR)||(nFlag == PM_TSTAT5E||nFlag == PM_PM5E) || (nFlag == PM_TSTAT5H)||(nFlag==PM_TSTAT5G))
                {
                    product_type = T3000_5EH_LCD_ADDRESS;
                }
                else if((nFlag == PM_TSTAT5A) ||(nFlag == PM_TSTAT5B) ||
                        (nFlag ==PM_TSTAT5C ) || (nFlag == PM_TSTAT5D) || (nFlag == PM_TSTAT5F))
                {
                    product_type =T3000_5ABCDFG_LED_ADDRESS;
                }
                //Code and comments by Fance
                //Use old_product_type to save the last value.
                //if this value is change ,it will reload the register value.
                //example:
                //For tstats 5A : product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 185
                //For tstats 6	  product_register_value[MODBUS_BAUDRATE]  ->  MODBUS_BAUDRATE = 110
                if(old_product_type!=product_type)
                {
                    old_product_type = product_type;
                    MyRegAddress.Change_Register_Table();
                }
                SwitchToPruductType(DLG_T3000_VIEW);


                bacnet_view_number = TYPE_TSTAT;

            }


            if (Scan_Product_ID == 210)
            {
                SwitchToPruductType(DLG_DIALOG_BOATMONITOR);
            }
        }
    }
    ado.CloseConn();

    g_bPauseMultiRead = FALSE;
}


///////////////////////////////////////////////////////////////////////////
//  Added by zgq;2010-11-29;添加初始化TreeCtrl，希望在程序初始化完成后
//  TreeCtrl能够反应设备的连接状况。
//  方法：遍历TreeCtrl，分别去连接每一个Node，并根据状态修改其显示
// void CMainFrame::InitTreeNodeConn()
// {
// 	// find the currently selected item
// 	HTREEITEM hCurSel = m_pTreeViewCrl->GetNextItem(TVI_ROOT, TVGN_ROOT);
//
// 	// report it to the user
// 	if (hCurSel == NULL)
// 	{
// 		AfxMessageBox(_T("There is no selected item"));
// 	}
// 	else
// 	{
// 		CString str;
// 		str.Format(_T("The currently selected item is \"%s\""),(LPCTSTR)m_pTreeViewCrl->GetItemText(hCurSel));
// 		//AfxMessageBox((LPCTSTR)str);
// 	}
//
// 	vector<HTREEITEM> szTreeItems;
// 	szTreeItems.push_back(hCurSel);
// 	GetAllTreeItems(hCurSel, szTreeItems );
//
// 	for( UINT i = 0 ; i < szTreeItems.size(); i++)
// 	{
// 		HTREEITEM hItem = szTreeItems[i];
// 		DoConnectToANode(hItem);
// 	}
// }


void CMainFrame::GetAllTreeItems( HTREEITEM hItem, vector<HTREEITEM>& szTreeItems  )
{
    HTREEITEM hTemp = m_pTreeViewCrl->GetNextItem(hItem, TVGN_NEXT);
    if (hTemp != NULL)
    {
        szTreeItems.push_back(hTemp);
        GetAllTreeItems(hTemp, szTreeItems);
    }

    {
        hTemp = m_pTreeViewCrl->GetNextItem(hItem, TVGN_CHILD);
        if (hTemp != NULL)
        {
            szTreeItems.push_back(hTemp);
            GetAllTreeItems(hTemp, szTreeItems);
        }
    }
}

// refresh_com 只有当这个值为0的时候才刷新串口那部分的状态,因为网络广播的 很快;可以频繁扫描，串口太慢了;
BOOL CMainFrame::CheckDeviceStatus(int refresh_com)
{
    bool find_new_device = false;

    for(UINT i=0; i<m_product.size(); i++)
    {
        //tree0412if(!g_bEnableRefreshTreeView || g_bPauseRefreshTree || g_bPauseMultiRead)
        if( g_bPauseRefreshTree || g_bPauseMultiRead)
            return false;
        if(no_mouse_keyboard_event_enable_refresh == false)	//如果突然有客户操作了，就不要在刷新treeview了;
            return false;


        BOOL bOnLine=FALSE;
        UINT nSerialNumber=0;

        bool temp_online = false;
        tree_product tp = m_product.at(i);
        if(m_strCurSubBuldingName.CompareNoCase(tp.BuildingInfo.strBuildingName)==0)
        {
            int nIDNode=tp.product_id;
            nSerialNumber=tp.serial_number;

            //int newnID=read_one(nID,6,2);
            /*需要先保存之前的通信协议;
            Get the protocol ,if it is bacnet ip,we compare the device id.
            */
            //如果strip不是空的就说明这个设备室挂在NC或LC等等下面的MODBUS  RS485设备
            //if((m_product.at(i).protocol == MODBUS_RS485) && (m_product.at(i).BuildingInfo.strIp.IsEmpty()))

            int temp_port = 0;
            temp_port = m_product.at(i).ncomport;
            if((m_product.at(i).protocol == MODBUS_RS485) && (temp_port > 0 ) && (m_product.at(i).BuildingInfo.strIp.IsEmpty()))
            {
                if(refresh_com !=0 )
                    continue;
                //register_critical_section.Lock();
                int nCom = GetLastOpenedComport();
                int temp_comunicationtype = GetLastCommunicationType();
                int temp_baudrate = GetLastSuccessBaudrate();
                //m_product.at(i).status = false;
                temp_online = false;
                SetCommunicationType(0);
                //close_com(); // 先不关闭;
                int nComPort = m_product.at(i).ncomport;
                int n_baudrate = m_product.at(i).baudrate;
                //38400是有一个zigbee 的 USB  它的波特率,所以也需要判断38400;
                if((n_baudrate != 19200) && (n_baudrate != 9600) && (n_baudrate != 38400))
                    n_baudrate = 19200;
                if(nComPort == 0)
                {
                    temp_online = false;
                    //m_product.at(i).status = false;
                    bOnLine=FALSE;
                    //register_critical_section.Unlock();
                    goto end_condition;
                }
                BOOL  bret = 0;
                if((nComPort>0) && (nComPort<20))
                {
                    //TRACE(_T("Open Com%d "),nComPort);
                    if(nComPort!=nCom)	//如果不等于当前选择的设备的串口，就不要检测状态;免得串口一开一关的.
                        continue;
                    // bret = open_com(nComPort);
                    bret = 1;
                }
                else
                {
                    bret = 0;
                }
                if (!bret)
                {
                    temp_online = false;
                    //m_product.at(i).status = false;
                    bOnLine=FALSE;
                    //register_critical_section.Unlock();
                    goto end_condition;
                }
                else
                {
                    //m_nbaudrat=19200;
                    //Change_BaudRate(19200);
                    Change_BaudRate(n_baudrate);

                    // read register offset 6
                    //int error = modbus_read_one_value( nID,nIDNode,6,5);
                    //nID=read_one(nIDNode,6,5);

                    unsigned short first_ten_reg[10];
                    int read_block_ret;
                    read_block_ret=Read_Multi(nIDNode,&first_ten_reg[0],0,10,3);


                    //TRACE(_T("%d = Read_One(%d)     "),nID,nIDNode);
                    /*
                    If an error was returned from the read,
                    we previously attempted to try again with a reduced baud rate.
                    However, a bug in the code meant this never was done correctly
                    and problems were reported when the baud rate was changed.
                    See discussion in ticket #14
                    Now we simply set the online flag to FALSE and give up.
                    */


                    if( read_block_ret <0)
                    {
                        temp_online = false;
                        //m_product.at(i).status = false;
                        bOnLine=FALSE;
                    }
                    else
                    {
                        // successful read of register offset 6
                        //unsigned short SerialNum[4];
                        //memset(SerialNum,0,sizeof(SerialNum));
                        int nRet=0;//
                        // read first 4 registers
                        //	nRet=modbus_read_multi_value(&SerialNum[0],nID,0,4,5);
                        //nRet=Read_Multi(nID,&SerialNum[0],0,4,5);
                        //memcpy((char *)SerialNum,(char *)first_ten_reg,4);

                        unsigned int nSerialNumberRead;

                        if(nRet>=0)  // 计算串口号
                        {
                            nSerialNumberRead=first_ten_reg[0]+first_ten_reg[1]*256+first_ten_reg[2]*256*256+first_ten_reg[3]*256*256*256;
                        }

                        if(nSerialNumber>=0)
                        {
                            if(nSerialNumberRead==nSerialNumber) // 取到串口号，并相等，说明online;
                            {
                                temp_online = true;
                                //m_product.at(i).status = true;
                                bOnLine=TRUE;
                            }
                        }
                    }
                }
                //close_com();//先不关
                //TRACE(_T(" CloseCom \r\n"));
end_condition :

                if(temp_comunicationtype == 0)
                {

                    //CString strComport = m_product.at(i).BuildingInfo.strComPort;
                    //CString strComNum = strComport.Mid(3);

                    //if(nCom !=65535)
                    if((nCom >0) && (nCom <=20))
                    {
                        SetCommunicationType(0);
                        //close_com();
                        //open_com(nCom);
                        if((temp_baudrate != 19200) && (temp_baudrate != 9600)  && (temp_baudrate != 38400))
                            temp_baudrate = 19200;
                        Change_BaudRate(temp_baudrate);

                        //TRACE(_T(" OpenCom  %d \r\n"),nCom);
                    }

                    //int nCom = _wtoi(strComNum);

                }
                SetCommunicationType(temp_comunicationtype);
                //register_critical_section.Unlock();

            }
            else if(m_product.at(i).protocol == PROTOCOL_GSM)
            {
                int found_index = -1;
                for (int m=0; m<m_tcp_connect_info.size(); m++)
                {
                    if(m_tcp_connect_info.at(m).serialnumber == m_product.at(i).serial_number)
                    {
                        found_index = m;
                        bOnLine = TRUE;
                        temp_online = true;
                        break;
                    }
                }

                if(found_index >=0)
                {
                    bOnLine = TRUE;
                    temp_online = true;
                }
                else
                {
                    bOnLine = FALSE;
                    temp_online = false;
                }

            }
            else if(m_product.at(i).protocol == PROTOCOL_REMOTE_IP)
            {
                continue;
            }
            else// if(m_product.at(i).protocol == MODBUS_TCPIP)
            {
                temp_online = false;
                //m_product.at(i).status = false;
                for (int x=0; x<(int)m_refresh_net_device_data.size(); x++)
                {
                    if(nSerialNumber == m_refresh_net_device_data.at(x).nSerial)
                    {
                        temp_online = true;
                        //m_product.at(i).status = true;
                        bOnLine = TRUE;
                        break;
                    }
                }
            }
        }
        m_product.at(i).status_last_time[2] = m_product.at(i).status_last_time[1] ;
        m_product.at(i).status_last_time[1] = m_product.at(i).status_last_time[0] ;
        m_product.at(i).status_last_time[0] = temp_online ;
        m_product.at(i).status = m_product.at(i).status_last_time[0] || m_product.at(i).status_last_time[1] || m_product.at(i).status_last_time[2];
    }


    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();

    //This function add by Fance
    //If the Database not contain the device wo scaned , then added into the database or update it;
    for (int y=0; y<(int)m_refresh_net_device_data.size(); y++)
    {
        bool db_exsit = false;
        int n_index = 0;
        bool db_need_update = false;
        if(m_refresh_net_device_data.at(y).nSerial <=0 )
            continue;
        for (int z=0; z<(int)m_product.size(); z++)
        {
            if(m_refresh_net_device_data.at(y).nSerial == m_product.at(z).serial_number)
            {
                n_index = z;
                db_exsit = true;
                break;
            }
        }
        CString str_object_instance;
        CString str_panel_number;
        CString str_hw_version;
        CString str_fw_version;
        str_hw_version.Format(_T("%u"),m_refresh_net_device_data.at(y).hw_version);
        str_fw_version.Format(_T("%u"),m_refresh_net_device_data.at(y).sw_version);

        str_object_instance.Format(_T("%u"),m_refresh_net_device_data.at(y).object_instance);
        str_panel_number.Format(_T("%u"),m_refresh_net_device_data.at(y).panal_number);
        if(db_exsit)	//数据库存在，就查看是否要更新;
        {
            if((m_refresh_net_device_data.at(y).ip_address.CompareNoCase(m_product.at(n_index).BuildingInfo.strIp) != 0) ||
                    (m_refresh_net_device_data.at(y).NetCard_Address.CompareNoCase(m_product.at(n_index).NetworkCard_Address) != 0) ||
                    (m_refresh_net_device_data.at(y).nport != m_product.at(n_index).ncomport) ||
                    (m_refresh_net_device_data.at(y).modbusID != m_product.at(n_index).product_id) ||
                    (m_refresh_net_device_data.at(y).parent_serial_number != m_product.at(n_index).note_parent_serial_number) ||
                    ((m_product.at(n_index).protocol != MODBUS_TCPIP) && (m_product.at(n_index).protocol != PROTOCOL_BACNET_IP) && (m_product.at(n_index).protocol != PROTOCOL_BIP_TO_MSTP)) ||
                    ((m_refresh_net_device_data.at(y).panal_number != m_product.at(n_index).panel_number) && (m_refresh_net_device_data.at(y).panal_number != 0)) ||
                    ((m_refresh_net_device_data.at(y).object_instance != m_product.at(n_index).object_instance) && (m_refresh_net_device_data.at(y).object_instance != 0)) ||
                    ((m_refresh_net_device_data.at(y).show_label_name.CompareNoCase(m_product.at(n_index).NameShowOnTree) != 0)&& (!m_refresh_net_device_data.at(y).show_label_name.IsEmpty())))
            {

                find_new_device = 1;
                CString strSql;
                CString str_ip_address_exist;
                CString str_n_port;
                CString str_serialid;
                CString str_modbus_id;
                CString str_Product_name_view;
                CString NetwordCard_Address;
                CString str_parents_serial;
                str_ip_address_exist = m_refresh_net_device_data.at(y).ip_address;
                str_n_port.Format(_T("%d"),m_refresh_net_device_data.at(y).nport);

                str_serialid.Format(_T("%u"),m_refresh_net_device_data.at(y).nSerial);
                str_modbus_id.Format(_T("%d"),m_refresh_net_device_data.at(y).modbusID);
                NetwordCard_Address=m_refresh_net_device_data.at(y).NetCard_Address;

                if(m_refresh_net_device_data.at(y).parent_serial_number != 0)
                {
                    str_parents_serial.Format(_T("%u"),m_refresh_net_device_data.at(y).parent_serial_number);
                }
                else
                {
                    str_parents_serial = _T("0");
                }

                try
                {
                    CString temp_pname;
                    CString temp_modbusid;
                    temp_modbusid.Format(_T("%d"),m_refresh_net_device_data.at(y).modbusID);
                    temp_pname = GetProductName(m_refresh_net_device_data.at(y).product_id);
                    if(m_refresh_net_device_data.at(y).show_label_name.IsEmpty())
                    {
                        str_Product_name_view = temp_pname + _T(":") + str_serialid + _T("-") + temp_modbusid + _T("-") + str_ip_address_exist;
                    }
                    //else if(m_refresh_net_device_data.at(y).product_id == PM_TSTAT7)	//TSTAT7 不支持写 label名字;
                    //{
                    //	str_Product_name_view = temp_pname + _T(":") + str_serialid + _T("-") + temp_modbusid + _T("-") + str_ip_address_exist;
                    //}
                    else
                    {
                        str_Product_name_view = m_refresh_net_device_data.at(y).show_label_name;
                    }

                    bool is_bacnet_device = false;
                    if((m_refresh_net_device_data.at(y).product_id == PM_MINIPANEL) || (m_refresh_net_device_data.at(y).product_id == PM_CM5))
                        is_bacnet_device = true;

                    //if(m_refresh_net_device_data.at(y).ip_address.CompareNoCase(m_product.at(n_index).BuildingInfo.strIp) != 0)
                    //{
                    if((m_refresh_net_device_data.at(y).object_instance != 0) && (m_refresh_net_device_data.at(y).panal_number != 0) && is_bacnet_device && (m_refresh_net_device_data.at(y).parent_serial_number != 0))
                    {
                        //str_Product_name_view = str_Product_name_view ;
                        CString temp_pro;
                        temp_pro.Format(_T("%u"),PROTOCOL_BIP_TO_MSTP);
                        strSql.Format(_T("update ALL_NODE set NetworkCard_Address='%s', Object_Instance = '%s' , Panal_Number = '%s' , Bautrate ='%s',Com_Port ='%s',Product_ID ='%s', Protocol ='%s',Product_name = '%s',Online_Status = 1 ,Parent_SerialNum = '%s' where Serial_ID = '%s'"),NetwordCard_Address,str_object_instance,str_panel_number,str_ip_address_exist,str_n_port,str_modbus_id,temp_pro,str_Product_name_view,str_parents_serial,str_serialid);
                    }
                    else
                        strSql.Format(_T("update ALL_NODE set NetworkCard_Address='%s', Object_Instance = '%s' , Panal_Number = '%s' ,  Bautrate ='%s',Com_Port ='%s',Product_ID ='%s', Protocol ='1',Product_name = '%s',Online_Status = 1,Parent_SerialNum = '%s' where Serial_ID = '%s'"),NetwordCard_Address,str_object_instance,str_panel_number,str_ip_address_exist,str_n_port,str_modbus_id,str_Product_name_view,str_parents_serial,str_serialid);
                    find_new_device = true;
                    //}
                    //else
                    //{
                    //	if((m_refresh_net_device_data.at(y).object_instance != 0) && (m_refresh_net_device_data.at(y).panal_number != 0) && is_bacnet_device)
                    //	{
                    //		CString temp_pro1;
                    //		temp_pro1.Format(_T("%u"),PROTOCOL_BIP_TO_MSTP);
                    //		strSql.Format(_T("update ALL_NODE set NetworkCard_Address='%s', Object_Instance = '%s' , Panal_Number = '%s' , Bautrate ='%s',Com_Port ='%s',Product_ID ='%s', Protocol ='%s',Product_name = '%s',Online_Status = 1,Parent_SerialNum = '%s' where Serial_ID = '%s'"),NetwordCard_Address,str_object_instance,str_panel_number,str_ip_address_exist,str_n_port,str_modbus_id,temp_pro1,str_Product_name_view,str_parents_serial,str_serialid);
                    //	}
                    //	else
                    //		strSql.Format(_T("update ALL_NODE set NetworkCard_Address='%s',  Bautrate ='%s',Com_Port ='%s',Product_ID ='%s', Protocol ='1',Online_Status = 1,Parent_SerialNum = '%s' where Serial_ID = '%s'"),NetwordCard_Address,str_ip_address_exist,str_n_port,str_modbus_id,str_parents_serial,str_serialid);
                    //}
                    bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
                }
                catch(_com_error *e)
                {
                    AfxMessageBox(e->ErrorMessage());
                }


                m_product.at(n_index).ncomport = m_refresh_net_device_data.at(y).nport;
                m_product.at(n_index).BuildingInfo.strIp = m_refresh_net_device_data.at(y).ip_address;
                m_product.at(n_index).product_id = m_refresh_net_device_data.at(y).modbusID;
            }

        }
        else			//不存在 就插入;
        {
            CString strSql;
            CString str_ip_address;
            CString str_n_port;
            CString str_serialid;
            CString product_name;
            CString modbusid;
            CString product_class_id;
            CString NetwordCard_Address;
            CString str_parents_serial;
            CString is_custom;
            /*m_pCon.CreateInstance(_T("ADODB.Connection"));
            m_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);*/

            modbusid.Format(_T("%d"),m_refresh_net_device_data.at(y).modbusID);

            str_ip_address = m_refresh_net_device_data.at(y).ip_address;
            str_n_port.Format(_T("%d"),m_refresh_net_device_data.at(y).nport);

            str_serialid.Format(_T("%u"),m_refresh_net_device_data.at(y).nSerial);
            product_class_id.Format(_T("%d"),m_refresh_net_device_data.at(y).product_id);
            if (m_refresh_net_device_data.at(y).product_id > 200)
            {
                is_custom = _T("1");
            }
            else
            {
                is_custom = _T("0");
            }
            product_name = GetProductName(m_refresh_net_device_data.at(y).product_id);
            if(product_name.IsEmpty())
            {
                if (m_refresh_net_device_data.at(y).product_id<200)
                {
                    continue;
                }
                product_name = m_refresh_net_device_data.at(y).show_label_name;
            }


            if(m_refresh_net_device_data.at(y).parent_serial_number != 0)
            {
                str_parents_serial.Format(_T("%u"),m_refresh_net_device_data.at(y).parent_serial_number);
            }
            else
            {
                str_parents_serial = _T("0");
            }
            find_new_device = true;
            product_name = product_name + _T(":") + str_serialid + _T("-") + modbusid + _T("-") + str_ip_address;
            NetwordCard_Address=m_refresh_net_device_data.at(y).NetCard_Address;
            //strSql.Format(_T("insert into ALL_NODE (MainBuilding_Name,Building_Name,Serial_ID,Floor_name,Room_name,Product_name,Product_class_ID,Product_ID,NetworkCard_Address,Screen_Name,Bautrate,Background_imgID,Hardware_Ver,Software_Ver,Com_Port,EPsize,Online_Status)   values('"+m_strCurMainBuildingName+"','"+m_strCurSubBuldingName+"','"+str_serialid+"','floor1','room1','"+product_name+"','"+product_class_id+"','"+modbusid+"','"+NetwordCard_Address+"','"+str_ip_address+"','T3000_Default_Building_PIC.bmp','0','0','"+str_n_port+"','0','1')"));
            bool is_bacnet_device = false;
            if((m_refresh_net_device_data.at(y).product_id == PM_MINIPANEL) || (m_refresh_net_device_data.at(y).product_id == PM_CM5))
                is_bacnet_device = true;
            if((m_refresh_net_device_data.at(y).object_instance != 0) && (m_refresh_net_device_data.at(y).panal_number != 0) && is_bacnet_device && (m_refresh_net_device_data.at(y).parent_serial_number != 0))
            {
                product_name = product_name ;
                CString temp_pro2;
                temp_pro2.Format(_T("%u"),PROTOCOL_BIP_TO_MSTP);
                strSql.Format(_T("insert into ALL_NODE (MainBuilding_Name,Building_Name,NetworkCard_Address,Serial_ID,Floor_name,Room_name,Product_name,Product_class_ID,Product_ID,Screen_Name,Bautrate,Background_imgID,Hardware_Ver,Software_Ver,Com_Port,EPsize,Protocol,Online_Status,Parent_SerialNum,Panal_Number,Object_Instance,Custom)   values('"+m_strCurMainBuildingName+"','"+m_strCurSubBuldingName+"','"+NetwordCard_Address+"','"+str_serialid+"','floor1','room1','"+product_name+"','"+product_class_id+"','"+modbusid+"','""','"+str_ip_address+"','T3000_Default_Building_PIC.bmp','"+str_hw_version+"','"+str_fw_version+"','"+str_n_port+"','0','"+temp_pro2+"','1','"+str_parents_serial +"' ,'"+str_panel_number +"' ,'"+str_object_instance +"' ,'"+is_custom +"' )"));
            }
            else
                strSql.Format(_T("insert into ALL_NODE (MainBuilding_Name,Building_Name,NetworkCard_Address,Serial_ID,Floor_name,Room_name,Product_name,Product_class_ID,Product_ID,Screen_Name,Bautrate,Background_imgID,Hardware_Ver,Software_Ver,Com_Port,EPsize,Online_Status,Parent_SerialNum,Panal_Number,Object_Instance,Custom)   values('"+m_strCurMainBuildingName+"','"+m_strCurSubBuldingName+"','"+NetwordCard_Address+"','"+str_serialid+"','floor1','room1','"+product_name+"','"+product_class_id+"','"+modbusid+"','""','"+str_ip_address+"','T3000_Default_Building_PIC.bmp','"+str_hw_version+"','"+str_fw_version+"','"+str_n_port+"','0','1','"+str_parents_serial +"' ,'"+str_panel_number +"' ,'"+str_object_instance +"' ,'"+is_custom +"' )"));

            try
            {

                bado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);
            }
            catch(_com_error *e)
            {
                AfxMessageBox(e->ErrorMessage());
            }

        }

    }
    bado.CloseConn();
    if(find_new_device)
        PostMessage(WM_MYMSG_REFRESHBUILDING,0,0);
    return TRUE;
}


LRESULT  CMainFrame::RefreshTreeViewMap(WPARAM wParam, LPARAM lParam)
{
    for(UINT i=0; i<m_product.size(); i++)
    {
        tree_product tp = m_product.at(i);
        if(tp.status>0)
            // 如果online，更新显示图片
        {
            if(selected_product_index == i)
            {
                //SetPaneConnectionPrompt(_T("Online!"));
            }
            //SetPaneConnectionPrompt(_T("Online!"));
            m_pTreeViewCrl->turn_item_image(tp.product_item ,true);

        }
        else  // 替换offline的图片
        {
            //SetPaneConnectionPrompt(_T("Offline!"));
            if(selected_product_index == i)
            {
                //SetPaneConnectionPrompt(_T("Offline!"));
            }
            m_pTreeViewCrl->turn_item_image(tp.product_item ,false);

            // 				if(nID==g_tstat_id)
            // 					memset(&multi_register_value[0],0,sizeof(multi_register_value));
        }
        if(g_selected_serialnumber == m_product.at(i).serial_number)
        {
            if(tp.status>0)
                bac_select_device_online = true;
            else
                bac_select_device_online = false;
        }
    }


    return 0;
}


LRESULT CMainFrame::Message_Scan_Product(WPARAM wParam, LPARAM lParam)
{
    OnScanDevice();
    return 0;
}


void CMainFrame::SuspendRefreshThread()
{
    m_bEnableRefreshTreeView = FALSE;
}

void CMainFrame::ContinueRefreshThread()
{
    m_bEnableRefreshTreeView = TRUE;
}


void CMainFrame::DoFreshAll()
{
    PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);
    //RefreshTreeView();
    if ((m_nCurView == 0) && (g_tstat_id != 0) && (g_tstat_id != 255))
    {
        ((CT3000View*)m_pViews[m_nCurView])->PostMessage(WM_FRESHVIEW,0,0)	;
    }

}


UINT _FreshTreeView(LPVOID pParam )
{


    CString g_strT3000LogString;
    CMainFrame* pMain = (CMainFrame*)pParam;
    int int_refresh_com = 0;
    while(1)
    {

        if (!pMain->m_frist_start)
        {
            Sleep(4000);
        }
        if(g_bPauseMultiRead)
        {
            Sleep(10);
            continue;
        }
        pMain->m_frist_start = false;
        while(1)
        {
            if(no_mouse_keyboard_event_enable_refresh)//判断如果一段时间无人操作，才刷新tree，要不然串口资源会经常冲突;
            {
                //g_strT3000LogString=_T("T3000 is free");
                //		CString* pstrInfo = new CString(g_strT3000LogString);
                //::SendMessage(MainFram_hwd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));
                break;
            }

            Sleep(100);
        }


        //continue;
        m_refresh_net_device_data.clear();



        WaitForSingleObject(Read_Mutex,INFINITE);//Add by Fance .
        if(b_pause_refresh_tree)
        {
            ReleaseMutex(Read_Mutex);//Add by Fance .
            continue;
        }

        //if(pMain->m_subNetLst.size()<=0)
        //{
        //	ReleaseMutex(Read_Mutex);//Add by Fance .
        //	continue;
        //}

        //这里每一步都要确认客服是不是在操作T3000,如果客户在操作（读写）就不要和客户抢资源;
        if(no_mouse_keyboard_event_enable_refresh == false)
        {
            ReleaseMutex(Read_Mutex);
            continue;
        }
        if((current_building_protocol == P_AUTO) || (current_building_protocol == P_MODBUS_TCP) || (current_building_protocol == P_BACNET_IP))
        {
            RefreshNetWorkDeviceListByUDPFunc();
        }

        if(no_mouse_keyboard_event_enable_refresh == false)
        {
            ReleaseMutex(Read_Mutex);
            continue;
        }
        if(!pMain->CheckDeviceStatus(int_refresh_com))
        {
            ReleaseMutex(Read_Mutex);
            continue;
        }
        if(no_mouse_keyboard_event_enable_refresh == false)
        {
            ReleaseMutex(Read_Mutex);
            continue;
        }
        pMain->DoFreshAll();
        ReleaseMutex(Read_Mutex);//Add by Fance .
        int_refresh_com = (++int_refresh_com) %4;

    }

    return 1;
}


LRESULT CMainFrame::OnAddTreeNode(WPARAM wParam, LPARAM lParam)
{
    ScanTstatInDB();

    //////////////////////////////////////////////////////////////////////////
    if(m_pScanner)
    {
        //////////////////////////////////////////////////////////////////////////
        CString strTemp;
        g_bPauseMultiRead=FALSE;
        KillTimer(SCAN_TIMER);
        m_wndWorkSpace.m_TreeCtrl.Invalidate();

        //SelectTreeNodeFromRecord();//scan 解决scan完后，点击所扫到的项，显示com不对问题。

        //////////////////////////////////////////////////////////////////////////
        delete m_pScanner;
        m_pScanner =NULL;
    }
    g_bEnableRefreshTreeView =TRUE;
    g_bPauseRefreshTree = FALSE;
    PostMessage(WM_REFRESH_TREEVIEW_MAP,0,0);//扫描完了之后关闭扫描窗口，还要刷新Treeview;
    return 1;
}

CString CMainFrame::GetScreenName(int nSerialNumber, int nModbusID)
{
    CString strSerialNum, strMID;
    strSerialNum.Format(_T("%d"), nSerialNumber);
    strMID.Format(_T("%d"), nModbusID);

    CString strScreenName = _T("Screen(S:") + strSerialNum+_T("--")+strMID + _T(")");

    return strScreenName;
}



LRESULT CMainFrame::OnHotKey(WPARAM wParam,LPARAM lParam)
{
    UINT fuModifiers = (UINT) LOWORD(lParam);  // key-modifier flags
    UINT uVirtKey = (UINT) HIWORD(lParam);     // virtual-key code

    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        Program_Window->Unreg_Hotkey();
        Screen_Window->Unreg_Hotkey();
        WeeklyRoutine_Window->Unreg_Hotkey();
        AnnualRoutine_Window->Unreg_Hotkey();
        Monitor_Window->Unreg_Hotkey();
    }
    //判断响应了什么热键
    if( MOD_ALT == fuModifiers && 'G' == uVirtKey )  //Screen
    {
        OnControlScreens();
        //AfxMessageBox(_T("你按下了组合键 alt + m"));
    }
    else if(MOD_ALT == fuModifiers && 'P' == uVirtKey)//Program
    {
        OnControlPrograms();
    }
    else if(MOD_ALT == fuModifiers && 'I' == uVirtKey)//Input
    {
        OnControlInputs();
    }
    else if(MOD_ALT == fuModifiers && 'O' == uVirtKey)//Output
    {
        OnControlOutputs();
    }
    else if(MOD_ALT == fuModifiers && 'V' == uVirtKey)//Variable
    {
        OnControlVariables();
    }
    else if(MOD_ALT == fuModifiers && 'L' == uVirtKey)
    {
        OnControlControllers();
    }
    else if(MOD_ALT == fuModifiers && 'S' == uVirtKey)
    {
        OnControlWeekly();
    }
    else if(MOD_ALT == fuModifiers && 'H' == uVirtKey)
    {
        OnControlAnnualroutines();
    }
    else if(MOD_ALT == fuModifiers && 'T' == uVirtKey)
    {
        OnControlMonitors();
    }
    else if(MOD_ALT == fuModifiers && 'A' == uVirtKey)
    {
        OnControlAlarmLog();
    }
    else if(MOD_ALT == fuModifiers && 'U' == uVirtKey)
    {
        OnControlCustomerunits();
    }
    else if(MOD_ALT == fuModifiers && 'C' == uVirtKey)
    {
        OnControlSettings();
    }
    else if(MOD_ALT == fuModifiers && 'B' == uVirtKey)
    {
        OnAddBuildingConfig();
    }
    else if(MOD_ALT == fuModifiers && 'D' == uVirtKey)
    {
        OnScanDevice();
    }
    else if((MOD_SHIFT | MOD_CONTROL | MOD_ALT) == fuModifiers && 'D' == uVirtKey)//Annual Routines
    {
        enable_show_debug_window = true;
    }
    else if((MOD_SHIFT | MOD_CONTROL | MOD_ALT) == fuModifiers && 'F' == uVirtKey)//Annual Routines
    {
        if(enable_show_debug_window)
            ShowDebugWindow();
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////
// for record last time tree control node click result

//

// write current click result to register table of windows.
const CString strRegRoot = _T("Software\\Temco T3000 Application\\T3000\\TreeNodeRecord\\");

const CString strSubnetRegEntry = _T("Subnet");
const CString strSubnetRegEntryValid = _T("SubnetValid");
const CString strFloorRegEntry = _T("Floor");
const CString strFloorRegEntryValid = _T("FloorValid");
const CString strRoomRegEntry = _T("Room");
const CString strRoomRegEntryValid = _T("RoomValid");
const CString strDeviceRegEntry = _T("Device");
const CString strDeviceRegEntryValid = _T("DeviceValid");


//void CMainFrame::SaveTreeNodeRecordToReg(HTREEITEM& htiCurSel)
//{
//	CRegKey reg;
//
//	if(reg.Create(HKEY_CURRENT_USER, strRegRoot) == ERROR_SUCCESS)
//	{
//		HTREEITEM htiParent = m_pTreeViewCrl->GetParentItem(htiCurSel);
//		WriteValueToReg(reg, htiCurSel);
//		while(htiParent)
//		{
//			WriteValueToReg(reg, htiParent);
//			htiParent = m_pTreeViewCrl->GetParentItem(htiParent);
//		}
//	}
//	else // 没有这个表项
//	{
//		ASSERT(0);
//	}
//
//	reg.Close();
//}


// m_nSubnetItemData = 9000;
// m_nFloorItemData = 1000;
// m_nRoomItemData = 2000;
// m_nDeviceItemData = 3000;
//BOOL CMainFrame::WriteValueToReg(CRegKey& reg, HTREEITEM& htiItem)
//{
//	if (!htiItem)
//	{
//		return FALSE;
//	}
//	int nData = m_pTreeViewCrl->GetItemData(htiItem);
//	CString strText = m_pTreeViewCrl->GetItemText(htiItem);
//
//	if (nData >= 1000 && nData < 2000) // floor
//	{
//		reg.SetStringValue(strFloorRegEntry, strText);
//		reg.SetDWORDValue(strFloorRegEntryValid, 1);
//	}
//	else if(nData >= 2000 && nData < 3000) // room
//	{
//		reg.SetStringValue(strRoomRegEntry, strText);
//		reg.SetDWORDValue(strRoomRegEntryValid, 1);
//	}
//	else if(nData >= 3000 && nData < 9000)	// device
//	{
//		reg.SetStringValue(strDeviceRegEntry, strText);
//		reg.SetDWORDValue(strDeviceRegEntryValid, 1);
//	}
//	else if(nData >= 9000) // subnet
//	{
//		reg.SetStringValue(strSubnetRegEntry, strText);
//		if(reg.SetDWORDValue(strSubnetRegEntryValid, 1) != ERROR_SUCCESS)
//		{
//			AfxMessageBox(_T("Failed write Registry!"));
//		}
//	}
//
//	return TRUE;
//
//}


// nFlag = 0, read subnet
//         = 1, read floor
//         = 2, read room
//         = 3, read device
//void CMainFrame::SelectTreeNodeFromRecord()
//{
//	CString strSubnetName, strFloorName, strRoomName, strDeviceName;
//	//int nSubnet, nFloor, nRoom, nDevice;
//
//	CRegKey reg;
//	if(reg.Open(HKEY_CURRENT_USER, strRegRoot) == ERROR_SUCCESS)
//	{
//		HTREEITEM htiRoot = m_pTreeViewCrl->GetRootItem();
//		HTREEITEM htiSel = GetLastSelNodeFromRecord(reg, htiRoot);
//		m_pTreeViewCrl->SelectItem(htiSel);
//	//	DoConnectToANode(htiSel);//scan 原来有这句的。
//
//	}
//	else // 没有这个表项
//	{
//		m_pTreeViewCrl->SelectItem(NULL);
//	}
//
//	reg.Close();
//}

//
HTREEITEM CMainFrame::GetLastSelNodeFromRecord(CRegKey& reg, HTREEITEM& htiRoot)
{
    HTREEITEM htiSel = NULL;
    CString strSubnetName, strFloorName, strRoomName, strDeviceName;
    DWORD nSubnet, nFloor, nRoom, nDevice;

    DWORD dwSize=64;
    CString strRet;
    LPTSTR  szRet = new TCHAR[64];
    ZeroMemory(szRet, 64);

    //////////////////////////////////////////////////////////////////////////
    // 先获得所有的标志位 和 name
    // subnet
    if(reg.QueryDWORDValue(strSubnetRegEntryValid, nSubnet) == ERROR_SUCCESS)
    {
        if(reg.QueryStringValue(strSubnetRegEntry, szRet, &dwSize) == ERROR_SUCCESS)
        {
            strSubnetName = CString(szRet);
        }
        else
        {
            ASSERT(0);
        }
    }
    else
    {
        nSubnet =0;
    }

    // floor
    if(reg.QueryDWORDValue(strFloorRegEntryValid, nFloor) == ERROR_SUCCESS)
    {
        ZeroMemory(szRet, 64);
        dwSize=64;
        if(reg.QueryStringValue(strFloorRegEntry, szRet, &dwSize) == ERROR_SUCCESS)
        {
            strFloorName = CString(szRet);
        }
        else
        {
            ASSERT(0);
        }
    }
    else
    {
        nFloor =0;
    }

    // room
    if(reg.QueryDWORDValue(strRoomRegEntryValid, nRoom) == ERROR_SUCCESS)
    {
        ZeroMemory(szRet, 64);
        dwSize=64;
        if(reg.QueryStringValue(strRoomRegEntry, szRet, &dwSize) == ERROR_SUCCESS)
        {
            strRoomName = CString(szRet);
        }
        else
        {
            ASSERT(0);
        }
    }
    else
    {
        nRoom =0;
    }

    // device
    if(reg.QueryDWORDValue(strDeviceRegEntryValid, nDevice) == ERROR_SUCCESS)
    {
        ZeroMemory(szRet, 64);
        dwSize=64;
        if(reg.QueryStringValue(strDeviceRegEntry, szRet, &dwSize) == ERROR_SUCCESS)
        {
            strDeviceName = CString(szRet);
        }
        else
        {
            ASSERT(0);
        }
    }
    else
    {
        nDevice =0;
    }

    /////////////////////////////////////////////////////////////////////////
    // 查找节点
    if(nSubnet == 1)
    {
        htiSel = SearchItemByName(htiRoot, strSubnetName);
    }
    else
    {
        return NULL;
    }

    HTREEITEM htiTemp = NULL;
    // check floor
    if (htiSel && nFloor == 1 ) // go on to search
    {
        htiTemp = SearchItemByName(htiSel, strFloorName);
    }

    // check room
    if (htiTemp)
    {
        htiSel = htiTemp;
        if(nRoom == 1)
        {
            htiTemp = SearchItemByName(htiSel, strRoomName);
        }
    }

    // check device
    if (htiTemp)
    {
        htiSel = htiTemp;
        if(nDevice == 1)
        {
            htiTemp = SearchItemByName(htiSel, strDeviceName);
            if (htiTemp)
            {
                htiSel = htiTemp;
            }
        }
    }


    delete [] szRet;
    //
    return htiSel;

}



//////////////////////////////////////////////////////////////////////////
// 根据树节点的name搜索一个节点并返回
// 如果有多个节点同名，那么返回第一个找到的
//
HTREEITEM CMainFrame::SearchItemByName(HTREEITEM& htiRoot, const CString& strItemName)
{
    CString strRoot = m_pTreeViewCrl->GetItemText(htiRoot);
    if (strItemName.CompareNoCase( strRoot ) == 0 )
    {
        return htiRoot;
    }


    HTREEITEM htiChild = m_pTreeViewCrl->GetChildItem(htiRoot);

    vector<HTREEITEM>  szTreeItem;

    if (htiChild)
    {

        CString strText = m_pTreeViewCrl->GetItemText(htiChild);
        if (strText.CompareNoCase(strItemName) == 0)
        {
            return htiChild;
        }

        szTreeItem.push_back(htiChild);
        HTREEITEM htiSibling = m_pTreeViewCrl->GetNextSiblingItem(htiChild);
        while( htiSibling )
        {
            CString strText = m_pTreeViewCrl->GetItemText(htiSibling);
            if (strText.CompareNoCase(strItemName) == 0)
            {
                return htiSibling;
            }
            szTreeItem.push_back(htiSibling);
            htiSibling = m_pTreeViewCrl->GetNextSiblingItem(htiSibling);
        }
    }

    for(UINT i = 0; i < szTreeItem.size(); i++)
    {
        HTREEITEM htiRet = SearchItemByName(szTreeItem[i], strItemName);

        if (htiRet)
        {
            return htiRet;
        }
    }

    return NULL;

}


// 为第一次运行导入数据库，如果不是第一次运行则不用提示
// 判断当前版本与注册表中版本是否一致，如一致则不用提示
// 如不一致，那么要提示，并把当前版本写入注册表
BOOL CMainFrame::ImportDataBaseForFirstRun()
{
    CString strFileVer = GetCurrentFileVersion();

    CRegKey reg;
    ReadFileVersionFromRegister(reg);

    if (strFileVer.CompareNoCase(m_strFileVersion) == 0) // equal
    {
        // do nothing
    }
    else
    {
        //CImportDatabaseDlg dlg;
        //dlg.DoModal();

        reg.SetStringValue(_T("FileVersion"), strFileVer);
    }


    return TRUE;
}



const CString c_strFileVersionPath = _T("Software\\Temco T3000 Application\\T3000\\FileVersion\\");


// 从注册表读fileversion
CString CMainFrame::ReadFileVersionFromRegister(CRegKey& reg)
{
    WCHAR szBuf[64] = {0};
    DWORD dwSize = 64;

    if(reg.Create(HKEY_CURRENT_USER, c_strFileVersionPath) == ERROR_SUCCESS)
    {
        if(reg.QueryStringValue(_T("FileVersion"), szBuf, &dwSize) == ERROR_SUCCESS)
        {
            m_strFileVersion = CString(szBuf);
        }
    }
    else // 没有这个表项
    {
        ASSERT(0);
    }

    return m_strFileVersion;
    reg.Close();
}


CString CMainFrame::GetCurrentFileVersion()
{

    WCHAR cPath[200];
    DWORD dwHandle,InfoSize;
    CString strVersion;
    ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度+

    InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
    if(InfoSize==0) return _T("None Version Supprot");
    char *InfoBuf = new char[InfoSize];
    GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
    unsigned int  cbTranslate = 0;
    struct LANGANDCODEPAGE
    {
        WORD wLanguage;
        WORD wCodePage;
    } *lpTranslate;
    VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
    // Read the file description for each language and code page.
    for( UINT i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
    {
        WCHAR  SubBlock[200];
        wsprintf( SubBlock,
                  TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);
        void *lpBuffer=NULL;
        unsigned int dwBytes=0;
        VerQueryValue(InfoBuf,
                      SubBlock,
                      &lpBuffer,
                      &dwBytes);
        //CString strTemp=(char *)lpBuffer;
        CString strTemp((WCHAR*)lpBuffer);
        strVersion=strTemp;

    }

    delete []InfoBuf;
    //char *InfoBuf = new char[InfoSize];
    return strVersion;
}


void CMainFrame::EnableMyToolBarButton(int nIndex, int nID, BOOL bEnable)
{
    return;
// 	if (bEnable)
// 	{
// 		m_wndToolBar.SetButtonInfo(nIndex,  nID,   TBBS_BUTTON,   0);
//
// 	}
// 	else
// 	{
// 		m_wndToolBar.SetButtonInfo(nIndex,   10000,   TBBS_BUTTON,   0);
// 	}

// 	return;
// 	m_wndToolBar.SetGrayDisabledButtons(TRUE);
// 	//m_wndToolBar.AutoGrayInactiveImages();
//
// 	DWORD dwID1 = ID_CONNECT2;
// 	DWORD dwID2 = ID_DISCONNECT2;
// 	DWORD dwID = m_wndToolBar.GetItemID(nIndex);
//
// 	CMFCToolBarButton* pBtn =m_wndToolBar.GetButton(nIndex);
//
// 	m_wndToolBar.SetShowTooltips(TRUE);
// 	pBtn->EnableWindow(FALSE);
//
// 	pBtn->SetStyle(TBBS_DISABLED);
//
//
//
// 	m_wndToolBar.UpdateButton(nIndex);
// 	//m_wndToolBar.EnableCustomizeButton(FALSE, ID_CONNECT2, _T("Connect"));
// 	//m_wndToolBar.SetButtonStyle(nIndex, TBBS_DISABLED);
}
//
// void CMainFrame::OnDatabaseTemcoproducts()
// {
//
//
// // 	CProInterface dlg;
// // 	dlg.ShowDialog();
//
//
// }

void CMainFrame::ReadExcel()
{
#if 0
    CString strPath;
    // 	m_Path.GetWindowText(strPath);


    _Application app;
    Workbooks books;
    _Workbook book;
    Worksheets sheets;
    _Worksheet sheet;
    Range range;

    //
// 	if (!app.CreateDispatch(_T("Excel.Application"),NULL))
// 	{
// 		AfxMessageBox(_T("Create Excel false!"));
// 		exit(1);
// 	}
    books.AttachDispatch(app.GetWorkbooks());
    book.AttachDispatch(books.Add(_variant_t(strPath)));
    //μ?μ?Worksheets
    sheets.AttachDispatch(book.GetWorksheets());
    sheet.AttachDispatch(sheets.GetItem(_variant_t("Sheet1")));
    //μ?μ?è?2?Cells
    range.AttachDispatch(sheet.GetCells());
//	CString sText[]={_T("编号"),_T("姓名"),_T("所属部门")};//标题
//	int temp = m_Grid.GetItemCount()+1;

// 	for (int setnum=0;setnum<m_Grid.GetItemCount()+1;setnum++)
// 	{
// 		for (int num=0;num<3;num++)
// 		{
// 			if (!setnum)
// 			{
// 				range.SetItem(_variant_t((long)(setnum+1)),_variant_t((long)(num+1)),//在这里写入标题
// 					_variant_t(sText[num]));
// 			}
// 			else
// 			{
// 				range.SetItem(_variant_t((long)(setnum+1)),_variant_t((long)(num+1)),//在这里写入数据
// 					_variant_t(m_Grid.GetItemText(setnum-1,num)));
// 			}
// 		}
// 	}
    app.SetVisible(true);
    range.ReleaseDispatch();
    sheet.ReleaseDispatch();
    sheets.ReleaseDispatch();
    book.ReleaseDispatch();
    books.ReleaseDispatch();
    app.ReleaseDispatch();

#endif
}

void CMainFrame::Tstat6_func()
{
    int num =0;
    for (int i =0; i<512; i++)
    {
        num = reg_tstat6[i];
        reg_tststold[num] = i;
    }

}

void CMainFrame::JudgeTstat6dbExist( CString strtable,CString strsql )
{
    CADO m_cado;
    m_cado.OnInitADOConn();
    bool ret = m_cado.IsHaveTable(m_cado,strtable);

    //不存在 创建数据库表
    if (!ret)
    {
        m_cado.m_pRecordset = m_cado.OpenRecordset(strsql);
        //初始化表
        //如果不初始化，则会有很多问题
        CString sql;
        sql.Format(_T("select * from %s"),strtable);
        m_cado.m_pRecordset = m_cado.OpenRecordset(sql);
        if (m_cado.m_pRecordset->EndOfFile)
        {

            for(int i = 0; i<512; i++)
            {
                try
                {
                    m_cado.m_pRecordset->AddNew();


                    m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(charr[i][0]));
                    m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
                    //	m_cado.m_pRecordset->PutCollect("Data",(_bstr_t)(i+1));

                    m_cado.m_pRecordset->PutCollect("Description",(_bstr_t)(charr[i][1]));



                    m_cado.m_pRecordset->Update();

                }

                catch(...)
                {

                }
            }
        }




    }
    m_cado.CloseConn();

}

void CMainFrame::Updata_db_tstat6( unsigned short imodel )
{
    CString strtable;
    if (imodel == PM_TSTAT6||imodel == PM_TSTAT5i||imodel == PM_TSTAT8)
        strtable = _T("Tstat6");
//     if (imodel == PM_TSTAT5i)
//         strtable = _T("Tstat5i");
    else if(imodel == PM_TSTAT7)
        strtable = _T("Tstat7");
    //CString strsql = _T("select * from Tstat6");
    //strtemp.Format(_T("update %s set name='%s' where num='%s'"),m_database,m_name,m_num);

    CADO m_cado;
    m_cado.OnInitADOConn();
//	bool ret = m_cado.IsHaveTable(m_cado,strtable);

    //不存在 创建数据库表
//	if (!ret)
//	{
    //	m_cado.m_pRecordset = m_cado.OpenRecordset(strsql);
    //初始化表
    //如果不初始化，则会有很多问题
    CString sql;
    sql.Format(_T("select * from %s"),strtable);
    m_cado.m_pRecordset = m_cado.OpenRecordset(sql);

    //	if (m_cado.m_pRecordset->EndOfFile)
    {

        for(int i = 0; i<512; i++)
        {
            try
            {
//					m_cado.m_pRecordset->AddNew();


//					m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(charr[i][0]));
//					m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
                m_cado.m_pRecordset->PutCollect("Data",(_bstr_t)(multi_register_value[i]));

//					m_cado.m_pRecordset->PutCollect("Description",(_bstr_t)(charr[i][1]));
                m_cado.m_pRecordset->MoveNext();


                m_cado.m_pRecordset->Update();

            }

            catch(...)
            {

            }
        }
    }
#if 0
    else if(m_cado.m_pRecordset->FirstOfFile)
    {
        for(int i = 0; i<512; i++)
        {
            try
            {
                //					m_cado.m_pRecordset->AddNew();


                //					m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(charr[i][0]));
                //					m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(i+1));
                m_cado.m_pRecordset->PutCollect("Data",(_bstr_t)(multi_register_value[i]));

                //					m_cado.m_pRecordset->PutCollect("Description",(_bstr_t)(charr[i][1]));


                m_cado.m_pRecordset->Update();

            }

            catch(...)
            {

            }

        }



    }
#endif
    m_cado.CloseConn();

}


void CMainFrame::JudgeTstat6SliderExist( CString strtable,CString strsql )
{

    CADO m_cado;
    m_cado.OnInitADOConn();
    bool ret = m_cado.IsHaveTable(m_cado,strtable);

    //不存在 创建数据库表
    if (!ret)
    {
        m_cado.m_pRecordset = m_cado.OpenRecordset(strsql);
        //初始化表
        //如果不初始化，则会有很多问题
        CString sql;
        sql.Format(_T("select * from %s"),strtable);
        m_cado.m_pRecordset = m_cado.OpenRecordset(sql);
        int m_flag =0;
        if (m_cado.m_pRecordset->EndOfFile)
        {

            for(int i = 0; i<12; i++)
            {
                try
                {
                    m_cado.m_pRecordset->AddNew();


                    m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(m_flag));
                    m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(m_slidertsta6[i]));
                    m_cado.m_pRecordset->Update();
                }

                catch(...)
                {

                }
            }
        }




    }
    m_cado.CloseConn();
}

void CMainFrame::UpdataSlider( int Flag )
{
    CString strtable;
// 	if (imodel == PM_TSTAT6)
// 		strtable = _T("Tstat6");
// 	else if(imodel == PM_TSTAT7)
// 		strtable = _T("Tstat7");
// 	//CString strsql = _T("select * from Tstat6");
// 	//strtemp.Format(_T("update %s set name='%s' where num='%s'"),m_database,m_name,m_num);

    strtable = _T("Sliderdb");
    CADO m_cado;
    m_cado.OnInitADOConn();
    //	bool ret = m_cado.IsHaveTable(m_cado,strtable);

    //不存在 创建数据库表
    //	if (!ret)
    //	{
    //	m_cado.m_pRecordset = m_cado.OpenRecordset(strsql);
    //初始化表
    //如果不初始化，则会有很多问题
    CString sql;
    sql.Format(_T("select * from %s"),strtable);
    m_cado.m_pRecordset = m_cado.OpenRecordset(sql);
    //if (m_cado.m_pRecordset->EndOfFile)
    {

        for(int i = 0; i<12; i++)
        {
            try
            {
                m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(Flag));
                m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(tstat6flex[i]));
                m_cado.m_pRecordset->MoveNext();


                m_cado.m_pRecordset->Update();

            }

            catch(...)
            {


            }


// 			int tstat6flex[12]={
// 				30,
// 				20,
// 				40,
// 				20,
// 				40,
// 				30,
// 				40,
// 				20,
// 				40,
// 				20,
// 				50,
// 				15
// 			};


// 			for(int i = 6;i<10;i++)
// 			{
// 				try
// 				{
// 					m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(Flag));
// 					m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(newtstat6[352+i]));
// 					m_cado.m_pRecordset->MoveNext();
//
//
// 					m_cado.m_pRecordset->Update();
//
// 				}
//
// 				catch(...)
// 				{
//
// 				}
// 			}
        }
    }

    m_cado.CloseConn();

}

void CMainFrame::ReadSlider()
{
    CString strtable;
    strtable = _T("Sliderdb");
    CADO m_cado;
    m_cado.OnInitADOConn();
    CString sql;
    sql.Format(_T("select * from %s"),strtable);
    m_cado.m_pRecordset = m_cado.OpenRecordset(sql);
    {

        for(int i = 0; i<12; i++)
        {
            try
            {
                m_cado.m_pRecordset->GetCollect("Block");
                m_slidertsta6[i] = m_cado.m_pRecordset->GetCollect("Address");
// 				m_cado.m_pRecordset->PutCollect("Block",(_bstr_t)(Flag));
// 				m_cado.m_pRecordset->PutCollect("Address",(_bstr_t)(newtstat6[345+i]));
                m_cado.m_pRecordset->MoveNext();


//				m_cado.m_pRecordset->Update();

            }

            catch(...)
            {

            }



        }
    }

    m_cado.CloseConn();


}

void CMainFrame::Treestatus()
{


}

//Code by Fance
//Used for receive all message from all dlg
DWORD WINAPI   CMainFrame::Get_All_Dlg_Message(LPVOID lpVoid)
{
    _MessageWriteOneInfo *My_Write_Struct=NULL;
    MSG msg;
    PeekMessage(&msg, NULL, MY_WRITE_ONE, MY_CLOSE, PM_REMOVE);
    while(true)
    {
        if(GetMessage(&msg,0,0,0)) //get msg from message queue
        {
            switch(msg.message)
            {
            case MY_WRITE_ONE:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();

                My_Write_Struct= (_MessageWriteOneInfo *)msg.wParam;
                product_register_value[My_Write_Struct->address] = My_Write_Struct->new_value;//先变过来，免得后台更新的时候 乱变。
                break;
            case MY_WRITE_ONE_LIST:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
            case MY_WRITE_MULTI_LIST:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
// 				My_Write_Struct= (_MessageWriteOneInfo_List *)msg.wParam;
// 				product_register_value[My_Write_Struct->address] = My_Write_Struct->new_value;//先变过来，免得后台更新的时候 乱变。
                break;
            case  MY_READ_ONE:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
                My_Write_Struct= (_MessageWriteOneInfo *)msg.wParam;
                break;
            case MY_INVOKE_ID:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
                break;
            case  MY_BAC_WRITE_LIST:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
                break;
            case MY_BAC_REFRESH_LIST:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
                break;
            case MY_BAC_REFRESH_ONE:
                MyCriticalSection.Lock();
                My_Receive_msg.push_back(msg);
                MyCriticalSection.Unlock();
                break;
            case MY_CLOSE:
                goto myend;
                break;
            }

            /*sort(My_Receive_msg.begin(), My_Receive_msg.end());
            My_Receive_msg.erase(unique(My_Receive_msg.begin(), My_Receive_msg.end()), My_Receive_msg.end());*/
        }
    }
myend:
    return 0;
}
//const int WRITE_ONE_SUCCESS_LIST = 1;
//const int WRITE_ONE_FAIL_LIST =2 ;
//const int WRITE_MULTI_SUCCESS_LIST =3 ;
//const int WRITE_MULTI_FAIL_LIST =4 ;

//Code by Fance
//Use background thread deal all data
DWORD WINAPI  CMainFrame::Translate_My_Message(LPVOID lpVoid)
{
    CMainFrame *pParent = (CMainFrame *)lpVoid;
    MSG msg;
    int resend_count=0;
    int temp_end_value=0;
    _MessageInvokeIDInfo *My_Invoke_Struct=NULL;
    while(1)
    {
        if(My_Receive_msg.size()>0)
        {
            MSG my_temp_msg = My_Receive_msg.at(0);
            switch(my_temp_msg.message)
            {
            case MY_WRITE_ONE:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageWriteOneInfo *My_Write_Struct = (_MessageWriteOneInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();

                if(write_one(My_Write_Struct->device_id, My_Write_Struct->address,My_Write_Struct->new_value,10)<0)
                {
                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_FAIL,(LPARAM)My_Write_Struct);
                }
                else
                {
                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_SUCCESS,(LPARAM)My_Write_Struct);
                }
            }
            break;
            case MY_WRITE_ONE_LIST:
            {
                MyCriticalSection.Lock();
                if (My_Receive_msg.size()<=0)
                {
                    return 0;
                }
                msg=My_Receive_msg.at(0);
                vector<MSG>::iterator it=My_Receive_msg.begin();
                //it++;
                //for (;it!=My_Receive_msg.end();)
                while(it!=My_Receive_msg.end())
                {
                    if (msg.hwnd==it->hwnd&&
                            msg.lParam==it->lParam&&
                            msg.message==it->message&&
                            msg.pt.x==it->pt.x&&
                            msg.pt.y==it->pt.y&&
                            msg.time==it->time&&
                            msg.wParam==it->wParam)
                    {

                        My_Receive_msg.erase(it);
                        it=	 My_Receive_msg.begin();
                    }
                    else
                    {
                        it++;
                    }
                }

                _MessageWriteOneInfo_List *My_Write_Struct = (_MessageWriteOneInfo_List *)msg.wParam;
                //	My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();

                if(write_one(My_Write_Struct->device_id, My_Write_Struct->address,My_Write_Struct->new_value,10)<0)
                {

                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_ONE_FAIL_LIST,(LPARAM)My_Write_Struct);
                }
                else
                {
                    product_register_value[My_Write_Struct->address]=My_Write_Struct->new_value;
                    if (My_Write_Struct->list_type==LIST_TYPE_INPUT_TSTAT)
                    {
                        if (My_Write_Struct->mCol==INPUT_RANGE)
                        {
                            if (My_Write_Struct->mRow>=1&&My_Write_Struct->mRow<=8)
                            {
                                //int m_sn=product_register_value[0]+product_register_value[1]*256+product_register_value[2]*256*256+product_register_value[3]*256*256*256;
                                //CBADO ado;
                                //ado.SetDBPath(g_strCurBuildingDatabasefilePath);
                                //ado.OnInitADOConn();
                                //CString sql;
                                //sql.Format(_T("Select * from Value_Range where CInputNo=%d and SN=%d"),My_Write_Struct->mRow,m_sn);
                                //ado.m_pRecordset=ado.OpenRecordset(sql);

                                //if (!ado.m_pRecordset->EndOfFile)//有表但是没有对应序列号的值
                                //{
                                //	sql.Format(_T("update Value_Range set CRange = %d where CInputNo=%d and SN=%d "),My_Write_Struct->db_value,My_Write_Struct->mRow,m_sn);
                                //	ado.m_pConnection->Execute(sql.GetString(),NULL,adCmdText);
                                //}
                                //else
                                //{
                                //	sql.Format(_T("Insert into Value_Range ( SN,CInputNo,CRange) values('%d','%d','%d')"),m_sn,My_Write_Struct->mRow,My_Write_Struct->db_value);
                                //	ado.m_pConnection->Execute(sql.GetString(),NULL,adCmdText);
                                //}
                                //ado.CloseRecordset();
                                //ado.CloseConn();
                            }


                            int ret=Read_Multi(g_tstat_id,&multi_register_value[MODBUS_TEMPRATURE_CHIP],MODBUS_TEMPRATURE_CHIP,20);
                            if (ret>0)
                            {
                                for (int i=0; i<20; i++)
                                {
                                    product_register_value[MODBUS_TEMPRATURE_CHIP+i]=multi_register_value[MODBUS_TEMPRATURE_CHIP+i];
                                }
                            }

                        }

                        if (product_type==T3000_6_ADDRESS)
                        {
                            LoadTstat_InputData();
                            //LoadTstat_OutputData();
                        }
                        //int const PM_CO2_NET = 32;
                        // int const PM_CO2_RS485 = 33;
                        else if (product_type==CS3000)
                        {
                            LoadInputData_CS3000();
                            //LoadOutputData_CS3000();
                        }
                    }
                    if (My_Write_Struct->list_type==LIST_TYPE_OUTPUT_TSTAT)
                    {
                        //LoadTstat_OutputData();
                        if (product_type==T3000_6_ADDRESS)
                        {
                            //LoadTstat_InputData();
                            LoadTstat_OutputData();
                        }
                        //int const PM_CO2_NET = 32;
                        // int const PM_CO2_RS485 = 33;
                        else if (product_type==CS3000)
                        {
                            //LoadInputData_CS3000();
                            LoadOutputData_CS3000();
                        }
                    }
                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_ONE_SUCCESS_LIST,(LPARAM)My_Write_Struct);
                }

            }
            break;
            case MY_WRITE_MULTI_LIST:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageWriteMultiInfo_List *My_Write_Struct = (_MessageWriteMultiInfo_List *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();

                if(Write_Multi(My_Write_Struct->device_id,My_Write_Struct->RegValue,My_Write_Struct->Start_Address,8,10)<0)
                {

                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_MULTI_FAIL_LIST,(LPARAM)My_Write_Struct);
                }
                else
                {
                    UNION_INPUT_NAME inputname;

                    inputname.char_name[0]=My_Write_Struct->RegValue[1];
                    inputname.char_name[1]=My_Write_Struct->RegValue[0];

                    inputname.char_name[2]=My_Write_Struct->RegValue[3];
                    inputname.char_name[3]=My_Write_Struct->RegValue[2];

                    inputname.char_name[4]=My_Write_Struct->RegValue[5];
                    inputname.char_name[5]=My_Write_Struct->RegValue[4];

                    inputname.char_name[6]=My_Write_Struct->RegValue[7];
                    inputname.char_name[7]=My_Write_Struct->RegValue[6];


                    for (int i=0; i<4; i++)
                    {
                        product_register_value[My_Write_Struct->Start_Address+i]=inputname.reg_value[i];
                    }



                    ::PostMessage(My_Write_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_MULTI_SUCCESS_LIST,(LPARAM)My_Write_Struct);
                }
            }
            break;
            case MY_READ_ONE:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageReadOneInfo *My_Read_Struct = (_MessageReadOneInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();
                int ret = read_one(My_Read_Struct->device_id, My_Read_Struct->address,10);
                if(ret<0)
                {
                    //::PostMessage(My_Read_Struct->hwnd,MY_READ_DATA_CALLBACK,(WPARAM)WRITE_FAIL,(LPARAM)My_Read_Struct);
                    if(My_Read_Struct!=NULL)
                        delete	My_Read_Struct;
                }
                else
                {
                    My_Read_Struct->new_value = ret;	//refresh the old value; post message to dlg deal the read data;
                    ::PostMessage(My_Read_Struct->hwnd,MY_READ_DATA_CALLBACK,(WPARAM)WRITE_SUCCESS,(LPARAM)My_Read_Struct);
                }


            }
            break;
            case MY_INVOKE_ID:
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                My_Invoke_Struct = (_MessageInvokeIDInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();
                for (int i=0; i<2000; i++) //10秒钟判断任务是否超时.
                {
                    if(tsm_invoke_id_free(My_Invoke_Struct->Invoke_ID))
                    {
                        ::PostMessage(MainFram_hwd,MY_RX_TX_COUNT,1,0);
                        ::PostMessage(My_Invoke_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_SUCCESS,(LPARAM)My_Invoke_Struct);
                        goto loop1;
                    }
                    else
                    {

                        //Sleep(30);
                        Sleep(5);
                        continue;
                    }
                }
                ::PostMessage(MainFram_hwd,MY_RX_TX_COUNT,0,0);
                ::PostMessage(My_Invoke_Struct->hwnd,MY_RESUME_DATA,(WPARAM)WRITE_FAIL,(LPARAM)My_Invoke_Struct);
                //			tsm_free_invoke_id (My_Invoke_Struct->Invoke_ID);
loop1:
                break;
            case MY_BAC_WRITE_LIST:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageWriteListInfo *My_WriteList_Struct = (_MessageWriteListInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();
                //temp_end_value = My_WriteList_Struct->end_instance;
                do
                {
                    if(My_WriteList_Struct->end_instance<=(My_WriteList_Struct->start_instance+4))
                    {
                        temp_end_value  =  My_WriteList_Struct->end_instance;
                        //continue;//如果大于这个范围，就continue;
                    }
                    else
                        temp_end_value = My_WriteList_Struct->start_instance + 4;

                    resend_count = 0;
                    do
                    {
                        resend_count ++;
                        if(resend_count>10)
                            break;
                        g_invoke_id =WritePrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,My_WriteList_Struct->start_instance,temp_end_value);
                        if(g_invoke_id>=0)
                        {
                            //if((unsigned char)My_WriteList_Struct->command == CONNECTED_WITH_DEVICE)
                            //{
                            //	connect_invoke_id = g_invoke_id;
                            //	connect_replay = true;
                            //}
                            //CString temp_cs_show;
                            //temp_cs_show.Empty();
                            Post_Invoke_ID_Monitor_Thread(MY_INVOKE_ID,g_invoke_id,My_WriteList_Struct->hWnd,My_WriteList_Struct->Write_Info,My_WriteList_Struct->ItemInfo.nRow,My_WriteList_Struct->ItemInfo.nCol);
                        }
                        //Post_Invoke_ID_Monitor_Thread(MY_INVOKE_ID,g_invoke_id,My_WriteList_Struct->hWnd);
                        Sleep(SEND_COMMAND_DELAY_TIME);
                    }
                    while (g_invoke_id<0);

                    My_WriteList_Struct->start_instance = temp_end_value + 1;
                }
                while (temp_end_value<My_WriteList_Struct->end_instance);

                //if(My_WriteList_Struct)		//删除 new 的东西;
                //	delete My_WriteList_Struct;


            }
            break;
            case MY_BAC_REFRESH_LIST:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageRefreshListInfo *My_WriteList_Struct = (_MessageRefreshListInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();
                //switch(My_WriteList_Struct->command)
                //{
                //case READVARIABLE_T3000:
                for (int i=0; i<My_WriteList_Struct->block_size; i++)
                {
                    resend_count = 0;
                    do
                    {
                        resend_count ++;
                        if(resend_count>10)
                            break;
                        if((unsigned char)My_WriteList_Struct->command == READALARM_T3000)//Because the Alarm list need to read one by one
                        {
                            //g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,i,i,My_WriteList_Struct->entitysize);
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_READ_ALARMLOG_REMAINDER + (BAC_READ_ALARMLOG_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_ALARMLOG_COUNT)
                                end_temp_instance = BAC_ALARMLOG_COUNT - 1;

                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_ALARMLOG_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READ_REMOTE_POINT)
                        {
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_REMOTE_POINT_GROUP_REMAINDER + (BAC_REMOTE_POINT_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_REMOTE_POINT_COUNT)
                                end_temp_instance = BAC_REMOTE_POINT_COUNT - 1;

                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_REMOTE_POINT_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READINPUT_T3000)
                        {
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_READ_INPUT_REMAINDER + (BAC_READ_INPUT_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_INPUT_ITEM_COUNT)
                                end_temp_instance = BAC_INPUT_ITEM_COUNT - 1;
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_INPUT_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READOUTPUT_T3000)
                        {
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_READ_OUTPUT_REMAINDER + (BAC_READ_OUTPUT_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_OUTPUT_ITEM_COUNT)
                                end_temp_instance = BAC_OUTPUT_ITEM_COUNT - 1;
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_OUTPUT_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READVARIABLE_T3000)
                        {
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_READ_VARIABLE_REMAINDER + (BAC_READ_VARIABLE_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_VARIABLE_ITEM_COUNT)
                                end_temp_instance = BAC_VARIABLE_ITEM_COUNT - 1;
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_VARIABLE_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READWEEKLYROUTINE_T3000)
                        {
                            int end_temp_instance = 0;
                            end_temp_instance = BAC_READ_SCHEDULE_REMAINDER + (BAC_READ_SCHEDULE_GROUP_NUMBER*i) ;
                            if(end_temp_instance >= BAC_SCHEDULE_COUNT)
                                end_temp_instance = BAC_SCHEDULE_COUNT - 1;
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_SCHEDULE_GROUP_NUMBER)*i,end_temp_instance,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READ_MISC)
                        {
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,0,0,My_WriteList_Struct->entitysize);
                        }
                        else if((unsigned char)My_WriteList_Struct->command == READANALOG_CUS_TABLE_T3000)
                        {
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,My_WriteList_Struct->start_instance,My_WriteList_Struct->end_instance,My_WriteList_Struct->entitysize);
                        }
                        else
                            g_invoke_id = GetPrivateData(My_WriteList_Struct->deviceid,My_WriteList_Struct->command,(BAC_READ_GROUP_NUMBER)*i,3+(BAC_READ_GROUP_NUMBER)*i,My_WriteList_Struct->entitysize);
                        Sleep(SEND_COMMAND_DELAY_TIME);
                    }
                    while (g_invoke_id<0);

                }

            }
            break;
            case MY_BAC_REFRESH_ONE:
            {
                MyCriticalSection.Lock();
                msg=My_Receive_msg.at(0);
                _MessageRefreshListInfo *My_Readone_Struct = (_MessageRefreshListInfo *)msg.wParam;
                My_Receive_msg.erase(My_Receive_msg.begin());
                MyCriticalSection.Unlock();
                resend_count = 0;
                do
                {
                    resend_count ++;
                    if(resend_count>10)
                        break;

                    g_invoke_id = GetPrivateData(My_Readone_Struct->deviceid,My_Readone_Struct->command,My_Readone_Struct->start_instance,My_Readone_Struct->end_instance,My_Readone_Struct->entitysize);
                    Sleep(SEND_COMMAND_DELAY_TIME);
                }
                while (g_invoke_id<0);

            }
            break;
            }

        }
        Sleep(10);
    }
    return 0;
}


void CMainFrame::OnDatabaseIonameconfig()
{
    // TODO: Add your command handler code here
    CIONameConfig ionameconfig;
    ionameconfig.DoModal();
}


void CMainFrame::OnDatabaseMbpoll()
{
    //// TODO: Add your command handler code here
    //if (mbPollDlgOpen == TRUE)
    //	{
    //	mbPoll->ShowWindow(SW_SHOW);
    //	return;
    //	}

    //mbPollDlgOpen = TRUE;

    //mbPoll = new CMbPoll(this);

    ////mbPoll->Create(IDD_MBPOLL, GetDesktopWindow());
    //mbPoll->Create(IDD_MBPOLL, this);
    //mbPoll->ShowWindow(SW_SHOW);

    if (is_connect())
    {
        if (g_CommunicationType==0)
        {
            OnDisconnect();
        }
        CString strHistotyFile=g_strExePth+_T("Modbus Poll.exe");
        ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
    }
    else
    {
        AfxMessageBox(_T("Please config the way of your connection!"));
        OnAddBuildingConfig();
        OnConnect();
    }


}



// LRESULT CMainFrame::OnMbpollClosed(WPARAM wParam, LPARAM lParam)
// {
//     m_pFreshMultiRegisters->ResumeThread();
//     m_pRefreshThread->ResumeThread();
// 	m_pFreshTree->ResumeThread();
// 	//mbPollDlgOpen = FALSE;
//
// 	//mbPoll->ShowWindow(FALSE);
//
//
//     return 0;
// }


//void CMainFrame::OnAppExit()
//{
//     OnDisconnect();
//	 OnDestroy();
//	// TODO: Add your command handler code here
//}
void CMainFrame::OnToolIsptoolforone()
{



    b_pause_refresh_tree = true;
    bool temp_status = g_bPauseMultiRead;
    g_bPauseMultiRead = true;
    int temp_type = GetCommunicationType();


    BOOL bDontLinger = FALSE;
    setsockopt( h_Broad, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
    closesocket(h_Broad);


    //	isp_product_id = m_product.at(selected_product_index).product_class_id;
    //	if (!((product_Node.BuildingInfo.strIp.CompareNoCase(_T("9600")) ==0)||(product_Node.BuildingInfo.strIp.CompareNoCase(_T("19200"))==0) ||(product_Node.BuildingInfo.strIp.CompareNoCase(_T(""))) == 0))
    SetCommunicationType(0);//关闭串口，供ISP 使用;
    close_com();

    CString ApplicationFolder;
    CString AutoFlashConfigPath;
// 	GetModuleFileName(NULL, ApplicationFolder.GetBuffer(MAX_PATH), MAX_PATH);
// 	PathRemoveFileSpec(ApplicationFolder.GetBuffer(MAX_PATH));
// 	ApplicationFolder.ReleaseBuffer();
// 	AutoFlashConfigPath = ApplicationFolder + _T("//AutoFlashFile.ini");
// 	WritePrivateProfileStringW(_T("Data"),_T("Command"),_T("1"),AutoFlashConfigPath);

    CString ISPtool_path;

    GetModuleFileName(NULL, ApplicationFolder.GetBuffer(MAX_PATH), MAX_PATH);
    PathRemoveFileSpec(ApplicationFolder.GetBuffer(MAX_PATH));
    ApplicationFolder.ReleaseBuffer();
    ISPtool_path = ApplicationFolder + _T("\\ISP.exe");
    WinExecAndWait(ISPtool_path,NULL,NULL,0);

    if(temp_type == 0)
    {
        int comport = GetLastOpenedComport();
        open_com(comport);
    }
    else
    {

    }
    SetCommunicationType(temp_type);

    //Fance Add. 在ISP 用完1234 4321 的端口之后，T3000 在重新打开使用，刷新listview 的网络设备要使用;
    h_Broad=::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    BOOL bBroadcast=TRUE;
    ::setsockopt(h_Broad,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));
    int iMode=1;
    ioctlsocket(h_Broad,FIONBIO, (u_long FAR*) &iMode);

    //SOCKADDR_IN bcast;
    h_bcast.sin_family=AF_INET;
    //bcast.sin_addr.s_addr=nBroadCastIP;
    h_bcast.sin_addr.s_addr=INADDR_BROADCAST;
    h_bcast.sin_port=htons(UDP_BROADCAST_PORT);

    //SOCKADDR_IN siBind;
    h_siBind.sin_family=AF_INET;
    h_siBind.sin_addr.s_addr=INADDR_ANY;
    h_siBind.sin_port=htons(RECV_RESPONSE_PORT);
    ::bind(h_Broad, (sockaddr*)&h_siBind,sizeof(h_siBind));
    b_pause_refresh_tree = false;
    g_bPauseMultiRead = temp_status;



    //MessageBox(_T("This part of code is recoding,Please use ISP.exe to update now."),_T("Notice"),MB_OK | MB_ICONINFORMATION);
    return;
}




void CMainFrame::OnViewCommunicatetraffic()
{

// 	 if(g_testmultiReadtraffic_dlg==NULL){
// 	 g_testmultiReadtraffic_dlg=new CTestMultiReadTraffic;
// 	 g_testmultiReadtraffic_dlg->Create(IDD_TEST_MULTI_READ,this);
// 	 g_testmultiReadtraffic_dlg->ShowWindow(SW_SHOW);
// 	 }
// 	 else
// 	 {
// 	  g_testmultiReadtraffic_dlg->ShowWindow(SW_SHOW);
// 	 }
}


void CMainFrame::OnControlMain()
{
    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == PROTOCOL_BIP_TO_MSTP) || (g_protocol == MODBUS_BACNET_MSTP))
    {
        OnControlSettings();
    }
    else
    {
        if (product_type == T3000_6_ADDRESS)
        {
            //bacnet_view_number = TYPE_TSTAT_MAIN_INFOR;
            bacnet_view_number = TYPE_TSTAT;
            SwitchToPruductType(DLG_T3000_VIEW);
        }
        else if (product_type == CS3000||product_register_value[7]==PM_T322AI||product_register_value[7]==PM_T38AI8AO6DO)
        {
            bacnet_view_number = TYPE_TSTAT;
            SwitchToPruductType(DLG_DIALOG_DEFAULT_T3000_VIEW);
        }
        else if (product_register_value[7] == PM_T3IOA)
        {

            SwitchToPruductType(DLG_DIALOGT38AI8AO);
        }

        else if (product_register_value[7]== PM_T38I13O)
        {

            SwitchToPruductType(DLG_DIALOGT38I13O_VIEW);
        }
        else if (product_register_value[7] == PM_T34AO) //T3
        {
            SwitchToPruductType(DLG_DIALOGT3_VIEW);
        }
        else if (product_register_value[7]== PM_T3PT10)
        {
            SwitchToPruductType(DLG_DIALOGT3PT10);
        }
        else if (product_register_value[7]==PM_T332AI)
        {
            SwitchToPruductType(DLG_DIALOGT332AI_VIEW);
        }
        else if (product_register_value[7]==PM_T36CT)
        {
            SwitchToPruductType(DLG_DIALOGT36CT);
        }
        else if (product_register_value[7]==PM_T38I13O)
        {
            SwitchToPruductType(DLG_DIALOGT38I13O_VIEW);
        }
        else if (product_register_value[7]==PM_T332AI)
        {
            SwitchToPruductType(DLG_DIALOGT332AI_VIEW);
        }
        else if (product_register_value[7]==PM_T3IOA)
        {
            SwitchToPruductType(DLG_DIALOGT38AI8AO);
        }
    }
    bacnet_view_number = TYPE_MAIN		;
}

void CMainFrame::OnControlInputs()
{
    // TODO: Add your command handler code here

    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_INPUT] != NULL)
        {
            if(pDialog[WINDOW_INPUT]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_INPUT]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_INPUT);
            Input_Window->m_input_list.SetFocus();
            bacnet_view_number = TYPE_INPUT;
            g_hwnd_now = m_input_dlg_hwnd;

        }

        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }


        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();

        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_INPUT);
        }
        else
        {
            //if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_INPUT);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }


    }
    else
    {
        if (!is_connect())
        {
            AfxMessageBox(_T("NO Connection,Please connect your device,fristly!"));
            return;
        }
        if (product_type==CS3000||product_register_value[7]==PM_TSTAT6||product_register_value[7]==PM_TSTAT5i||product_register_value[7]==PM_TSTAT7||product_register_value[7]==PM_TSTAT8)
        {

            SwitchToPruductType(DLG_DIALOG_TSTAT_INPUT_VIEW);
        }
        else if (product_type == T3000_T3_MODULES )
        {
            SwitchToPruductType(DLG_DIALOG_T3_INPUTS_VIEW);
        }
        else
        {
            MessageBox(_T("This function don't support this product!\r\n"));
        }

    }
    bacnet_view_number = TYPE_INPUT		;
}


void CMainFrame::OnControlPrograms()
{
    // TODO: Add your command handler code here


    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }

        if(pDialog[WINDOW_PROGRAM] != NULL)
        {
            Program_Window->Unreg_Hotkey();
            Screen_Window->Unreg_Hotkey();
            WeeklyRoutine_Window->Unreg_Hotkey();
            AnnualRoutine_Window->Unreg_Hotkey();
            Monitor_Window->Unreg_Hotkey();
            if(pDialog[WINDOW_PROGRAM]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_PROGRAM]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_PROGRAM);
            Program_Window->m_program_list.SetFocus();
            Program_Window->Reg_Hotkey();
            bacnet_view_number = TYPE_PROGRAM;
            g_hwnd_now = m_pragram_dlg_hwnd;
        }


        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_PROGRAM);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_PROGRAM);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }

    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}


void CMainFrame::OnControlOutputs()
{
    // TODO: Add your command handler code here


    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_OUTPUT] != NULL)
        {
            if(pDialog[WINDOW_OUTPUT]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_OUTPUT]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_OUTPUT);
            Output_Window->m_output_list.SetFocus();
            bacnet_view_number = TYPE_OUTPUT;
            g_hwnd_now = m_output_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }

        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();
        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_OUTPUT);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_OUTPUT);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }

    }
    else
    {

        if (product_type==T3000_6_ADDRESS||product_register_value[7]==PM_CS_RSM_AC||product_register_value[7]==PM_CS_RSM_DC)
        {
            SwitchToPruductType(DLG_DIALOG_TSTAT_OUTPUT_VIEW);
            bacnet_view_number = TYPE_OUTPUT;
        }
        else if (product_type == T3000_T3_MODULES )
        {
            SwitchToPruductType(DLG_DIALOG_T3_OUTPUTS_VIEW);
            bacnet_view_number = TYPE_OUTPUT;
        }
        else
        {
            MessageBox(_T("This function don't support this product!\r\n"));
        }
        //MessageBox(_T("This function only support bacnet protocol!\r\nPlease select a bacnet product first."));
    }
}


void CMainFrame::OnControlVariables()
{
    // TODO: Add your command handler code here
    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_VARIABLE] != NULL)
        {
            if(pDialog[WINDOW_VARIABLE]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_VARIABLE]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_VARIABLE);
            Variable_Window->m_variable_list.SetFocus();
            bacnet_view_number = TYPE_VARIABLE;
            g_hwnd_now = m_variable_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }

        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();

        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_VARIABLE);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_VARIABLE);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }


    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}


void CMainFrame::OnControlWeekly()
{
    // TODO: Add your command handler code here
    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level !=	LOGIN_SUCCESS_ROUTINE_MODE) &&
                (m_user_level != LOGIN_SUCCESS_FULL_ACCESS) &&
                (m_user_level != LOGIN_SUCCESS_READ_ONLY))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        if(pDialog[WINDOW_WEEKLY] != NULL)
        {
            Program_Window->Unreg_Hotkey();
            Screen_Window->Unreg_Hotkey();
            WeeklyRoutine_Window->Unreg_Hotkey();
            AnnualRoutine_Window->Unreg_Hotkey();
            Monitor_Window->Unreg_Hotkey();
            if(pDialog[WINDOW_WEEKLY]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_WEEKLY]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_WEEKLY);
            WeeklyRoutine_Window->m_weeklyr_list.SetFocus();
            WeeklyRoutine_Window->Reg_Hotkey();
            bacnet_view_number = TYPE_WEEKLY;
            g_hwnd_now = m_weekly_dlg_hwnd;
        }

        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_WEEKLY);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_WEEKLY);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }


    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}

#include "TStatScheduleDlg.h"
void CMainFrame::OnControlAnnualroutines()
{
    // TODO: Add your command handler code here

    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level !=	LOGIN_SUCCESS_ROUTINE_MODE) &&
                (m_user_level != LOGIN_SUCCESS_FULL_ACCESS) &&
                (m_user_level != LOGIN_SUCCESS_READ_ONLY))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        if(pDialog[WINDOW_ANNUAL] != NULL)
        {
            Program_Window->Unreg_Hotkey();
            Screen_Window->Unreg_Hotkey();
            WeeklyRoutine_Window->Unreg_Hotkey();
            AnnualRoutine_Window->Unreg_Hotkey();
            Monitor_Window->Unreg_Hotkey();
            if(pDialog[WINDOW_ANNUAL]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_ANNUAL]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_ANNUAL);
            AnnualRoutine_Window->m_annualr_list.SetFocus();
            AnnualRoutine_Window->Reg_Hotkey();
            bacnet_view_number = TYPE_ANNUAL;
            g_hwnd_now = m_annual_dlg_hwnd;
        }

        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_ANNUAL);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_ANNUAL);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }
    }
    else
    {

        if(product_register_value[7]==PM_TSTAT5i||product_register_value[7]==PM_TSTAT6||product_register_value[7]==PM_TSTAT7||product_register_value[7]==PM_TSTAT8)
        {

            g_bPauseMultiRead = TRUE;
            CTStatScheduleDlg dlg;
            dlg.DoModal();
            g_bPauseMultiRead = FALSE;
        }
        else
            MessageBox(_T("This function don't support this product!\r\n"));
    }
}
#include "ParameterDlg.h"
void CMainFrame::OnControlSettings()
{
    // TODO: Add your command handler code here
    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == PROTOCOL_BIP_TO_MSTP) || (g_protocol == MODBUS_BACNET_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_SETTING] != NULL)
        {
            if(pDialog[WINDOW_SETTING]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_SETTING]->ShowWindow(SW_SHOW);
            }
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_SETTING);
            bacnet_view_number = TYPE_SETTING;
            g_hwnd_now = m_setting_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();
        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_SETTING);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_SETTING);
        }
    }
    else
    {
        if(product_register_value[7]==PM_TSTAT5i||product_register_value[7]==PM_TSTAT6||product_register_value[7]==PM_TSTAT7||product_register_value[7]==PM_TSTAT8)
        {
            CParameterDlg dlg(this,GetProductName(product_register_value[7]));
            dlg.DoModal();
        }
        else
            MessageBox(_T("This function don't support this product!\r\n"));
    }
}


void CMainFrame::OnMiscellaneousLoaddescriptors()
{
    // TODO: Add your command handler code here
    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_ALL);
        else
            MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}


void CMainFrame::OnMiscellaneousUpdatemini()
{
    // TODO: Add your command handler code here

    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,WRITEPRGFLASH_COMMAND);
        else
            MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);

    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}

//#include "BacnetController.h"
void CMainFrame::OnControlControllers()
{
    // TODO: Add your command handler code here

    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_CONTROLLER] != NULL)
        {
            if(pDialog[WINDOW_CONTROLLER]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_CONTROLLER]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_CONTROLLER);
            Controller_Window->m_controller_list.SetFocus();
            bacnet_view_number = TYPE_CONTROLLER;
            g_hwnd_now = m_controller_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();

        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_CONTROLLER);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_CONTROLLER);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }
    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }
}

void CMainFrame::OnControlScreens()
{

    //bac_cm5_graphic = true;
    // TODO: Add your command handler code here
//	CBacnetScreenEdit Dlg;
//	Dlg.DoModal();
//	return;

    if((g_protocol == PROTOCOL_BACNET_IP) || (g_protocol == MODBUS_BACNET_MSTP) || (g_protocol == PROTOCOL_BIP_TO_MSTP))
    {
        if((m_user_level !=	LOGIN_SUCCESS_GRAPHIC_MODE) &&
                (m_user_level != LOGIN_SUCCESS_FULL_ACCESS) &&
                (m_user_level != LOGIN_SUCCESS_READ_ONLY))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }

        if(pDialog[WINDOW_SCREEN] != NULL)
        {
            Program_Window->Unreg_Hotkey();
            Screen_Window->Unreg_Hotkey();
            WeeklyRoutine_Window->Unreg_Hotkey();
            AnnualRoutine_Window->Unreg_Hotkey();
            Monitor_Window->Unreg_Hotkey();
            if(pDialog[WINDOW_SCREEN]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_SCREEN]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_SCREEN);
            Screen_Window->m_screen_list.SetFocus();
            Screen_Window->Reg_Hotkey();
            bacnet_view_number = TYPE_SCREENS;
            g_hwnd_now = m_screen_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        if(g_protocol == PROTOCOL_BIP_TO_MSTP)
        {
            Create_Thread_Read_Item(TYPE_SCREENS);
        }
        else
        {
            if(bac_select_device_online)
                ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_SCREENS);
            //else
            //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
        }
    }
    else
    {
        if(product_register_value[7]==PM_TSTAT5i||product_register_value[7]==PM_TSTAT6||product_register_value[7]==PM_TSTAT7||product_register_value[7]==PM_TSTAT8)
        {
            SwitchToGraphicView();
        }
        else
        {
            MessageBox(_T("Can't support Graphic"));
        }
        //
    }
}
void CMainFrame::OnHelpGetlanguageconfigfile()
{

}
void CMainFrame::OnLanguageEnglish()
{
    CString infor;
    if (g_language==0)
    {
        infor=gLoadString(MESSAGEBOX,_T("1"));
        AfxMessageBox(infor);
    }
    else
    {
        theApp.SetLanguage(0);
        infor=gLoadString(MESSAGEBOX,_T("2"));
        AfxMessageBox(infor);
    }

}
void CMainFrame::OnLanguage34010()
{
// 	CString infor;
// 	if (g_language==1)
// 	 {
// 		 infor=gLoadString(MESSAGEBOX,_T("3"));
// 		 AfxMessageBox(infor);
// 	 }
// 	 else
// 	 {
// 		 theApp.SetLanguage(1);
// 		 infor=gLoadString(MESSAGEBOX,_T("4"));
// 		 AfxMessageBox(infor);
// 	 }
}


void CMainFrame::OnLanguage34006()
{

}


void CMainFrame::OnControlMonitors()
{
    // TODO: Add your command handler code here

    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if((m_user_level ==	LOGIN_SUCCESS_GRAPHIC_MODE) ||
                (m_user_level == LOGIN_SUCCESS_ROUTINE_MODE))
        {
            MessageBox(_T("Please use the administrator to access data!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
            return;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        if(pDialog[WINDOW_MONITOR] != NULL)
        {
            Program_Window->Unreg_Hotkey();
            Screen_Window->Unreg_Hotkey();
            WeeklyRoutine_Window->Unreg_Hotkey();
            AnnualRoutine_Window->Unreg_Hotkey();
            Monitor_Window->Unreg_Hotkey();
            if(pDialog[WINDOW_MONITOR]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_MONITOR]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_MONITOR);
            Monitor_Window->m_monitor_list.SetFocus();
            Monitor_Window->Reg_Hotkey();
            bacnet_view_number = TYPE_MONITOR;
            g_hwnd_now = m_monitor_dlg_hwnd;
        }



        if(bac_select_device_online)
        {
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_MONITOR);
            Post_Refresh_Message(g_bac_instance,READ_MISC,0,0,sizeof(Str_MISC),1);
        }
        //else
        //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        MessageBox(_T("This function don't support this product!\r\n"));
    }

    //CBacnetMonitor Dlg;
    //Dlg.DoModal();
}
void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect)
{
    CFrameWndEx::OnSizing(fwSide, pRect);

    // TODO: Add your message handler code here
}
void CMainFrame::OnToolRegisterviewer()
{
    // TODO: Add your command handler code here
    CRegisterViewerDlg dlg;
    dlg.DoModal();
}

#include "CM5/mygdiplus.h"
void CMainFrame::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    if(ScreenEdit_Window)
    {
        if(ScreenEdit_Window->IsWindowVisible())
            ::PostMessage(m_screenedit_dlg_hwnd,MY_REDRAW_WINDOW,NULL,NULL);
    }
    if(User_Login_Window)
    {
        if(m_user_login_hwnd != NULL)
        {
            if(User_Login_Window->IsWindowVisible())
                ::PostMessage(m_user_login_hwnd,MY_REDRAW_WINDOW,NULL,NULL);
        }

    }
    if(AlarmWindow_Window)
    {
        ::PostMessage(m_alarmwindow_dlg_hwnd,MY_REDRAW_WINDOW,NULL,NULL);
    }
    if(b_create_status)
    {
        CRect temprec;
        m_wndStatusBar.GetWindowRect(&temprec);

        statusbar->SetWindowPos(&wndTop,temprec.left,temprec.top,temprec.Width(),temprec.Height(),SWP_NOACTIVATE | SWP_SHOWWINDOW );
    }


    // TODO: Add your message handler code here
    // Do not call CFrameWndEx::OnPaint() for painting messages
}


void CMainFrame::OnDatabaseBacnettool()
{
    //CBacnetAlarmWindow dlg;
    //dlg.DoModal();
    CBacnetTool dlg;
    dlg.DoModal();
    // TODO: Add your command handler code here
}

void CMainFrame::OnControlAlarmLog()
{
    // TODO: Add your command handler code here
    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if(pDialog[WINDOW_ALARMLOG] != NULL)
        {
            if(pDialog[WINDOW_ALARMLOG]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_ALARMLOG]->ShowWindow(SW_SHOW);
            }
            //((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetFocus();
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(WINDOW_ALARMLOG);
            AlarmLog_Window->m_alarmlog_list.SetFocus();
            bacnet_view_number = TYPE_ALARMLOG;
            g_hwnd_now = m_alarmlog_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }

        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();
        if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_ALARMLOG);
        //else
        //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        MessageBox(_T("This function only support bacnet protocol!\r\nPlease select a bacnet product first."));
    }
}


void CMainFrame::OnControlCustomerunits()
{
#ifdef test_ptp
    int nret = 0;
    nret = GetPrivateData(1,READUNIT_T3000,0,	0,sizeof(Str_Units_element));
    Sleep(1);
#endif
#ifndef test_ptp
    // TODO: Add your command handler code here
    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_READ_CUSTOMER_UNIT);
        else
            MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        MessageBox(_T("This function only support bacnet protocol!\r\nPlease select a bacnet product first."));
    }
#endif
}


void CMainFrame::OnMenuCheckupdate()
{

    CT3000UpdateDlg dlg;
    dlg.DoModal();
}


void CMainFrame::OnDatabasePv()
{
    // TODO: Add your command handler code here
    //AfxMessageBox(_T("Developing....."));
    //return;
    CLoginDlg Dlg(g_buser_log_in);
    if (IDOK== Dlg.DoModal())
    {
        CPVDlg dlg;
        dlg.DoModal();
    }
    else
    {
        AfxMessageBox(_T("Loging.....fail!"));
    }



}


//Add by Fance 14/05/21
//When user want to update the firmware ,run this code to  get firmware and call ISP.exe to flash firmware.
void CMainFrame::OnHelpUpdatefirmware()
{
    // TODO: Add your command handler code here
#if 0
    MessageBox(_T("This function is still under develepment!"),_T("Notice"),MB_OK | MB_ICONINFORMATION);
    return;
    if(m_product.at(selected_product_index).status == false)//说明不在线;
    {
        if(IDNO == MessageBox(_T("The device you selected is not on line or the communication is bad, are you sure you want to update!"),_T("Notice"),MB_YESNO | MB_ICONINFORMATION))
            return;
    }
#endif
    b_pause_refresh_tree = true;
    bool temp_status = g_bPauseMultiRead;
    g_bPauseMultiRead = true;
    int temp_type = GetCommunicationType();


    BOOL bDontLinger = FALSE;
    setsockopt( h_Broad, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
    closesocket(h_Broad);

    m_product_isp_auto_flash.baudrate = m_product.at(selected_product_index).baudrate;
    m_product_isp_auto_flash.BuildingInfo.strIp = m_product.at(selected_product_index).BuildingInfo.strIp;
    m_product_isp_auto_flash.ncomport =  m_product.at(selected_product_index).ncomport;

    m_product_isp_auto_flash.product_class_id =  m_product.at(selected_product_index).product_class_id;
    m_product_isp_auto_flash.product_id =  m_product.at(selected_product_index).product_id;

//	isp_product_id = m_product.at(selected_product_index).product_class_id;
//	if (!((product_Node.BuildingInfo.strIp.CompareNoCase(_T("9600")) ==0)||(product_Node.BuildingInfo.strIp.CompareNoCase(_T("19200"))==0) ||(product_Node.BuildingInfo.strIp.CompareNoCase(_T(""))) == 0))
    SetCommunicationType(0);//关闭串口，供ISP 使用;
    close_com();
    Dowmloadfile Dlg;
    Dlg.DoModal();

    if(temp_type == 0)
    {
        int comport = GetLastOpenedComport();
        open_com(comport);
    }
    else
    {

    }
    SetCommunicationType(temp_type);

    //Fance Add. 在ISP 用完1234 4321 的端口之后，T3000 在重新打开使用，刷新listview 的网络设备要使用;
    h_Broad=::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    BOOL bBroadcast=TRUE;
    ::setsockopt(h_Broad,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));
    int iMode=1;
    ioctlsocket(h_Broad,FIONBIO, (u_long FAR*) &iMode);

    //SOCKADDR_IN bcast;
    h_bcast.sin_family=AF_INET;
    //bcast.sin_addr.s_addr=nBroadCastIP;
    h_bcast.sin_addr.s_addr=INADDR_BROADCAST;
    h_bcast.sin_port=htons(UDP_BROADCAST_PORT);

    //SOCKADDR_IN siBind;
    h_siBind.sin_family=AF_INET;
    h_siBind.sin_addr.s_addr=INADDR_ANY;
    h_siBind.sin_port=htons(RECV_RESPONSE_PORT);
    ::bind(h_Broad, (sockaddr*)&h_siBind,sizeof(h_siBind));
    b_pause_refresh_tree = false;
    g_bPauseMultiRead = temp_status;
}

void CMainFrame::OnControlTstat()
{
    // TODO: Add your command handler code here
#ifdef test_ptp
    char my_port[50];

    CString temp_cs11;


    srand((unsigned)time(NULL));
    unsigned int temp_value;
    temp_value = rand()%(0x3FFFFF);
    g_Print.Format(_T("The initial T3000 Object Instance value is %d"),temp_value);
    DFTrace(g_Print);
    Device_Set_Object_Instance_Number(temp_value);
    address_init();
    Init_Service_Handlers();






    //temp_cs.Format(_T("COM%d"),g_com);
    temp_cs11.Format(_T("COM%d"),5);
    char cTemp11[255];
    memset(cTemp11,0,255);
    WideCharToMultiByte( CP_ACP, 0, temp_cs11.GetBuffer(), -1, cTemp11, 255, NULL, NULL );
    temp_cs11.ReleaseBuffer();
    sprintf(my_port,cTemp11);

    dlmstp_set_baud_rate(19200);
    dl_ptp_init(my_port);

    set_datalink_protocol(4);

    //::PostMessage( BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,1);




    g_bac_instance = 0;



    return;
#endif
    if(g_protocol == PROTOCOL_BACNET_IP)
    {
        if(pDialog[WINDOW_TSTAT] != NULL)
        {
            if(pDialog[WINDOW_TSTAT]->IsWindowVisible() == false)
            {
                for (int i=0; i<WINDOW_TAB_COUNT; i++)
                {
                    pDialog[i]->ShowWindow(SW_HIDE);
                }
                pDialog[WINDOW_REMOTE_POINT]->ShowWindow(SW_SHOW);
            }
            ((CDialogCM5_BacNet*)m_pViews[DLG_BACNET_VIEW])->m_bac_main_tab.SetCurSel(12);	//第12个插入的是远端的点;
            Remote_Point_Window->m_remote_point_list.SetFocus();
            bacnet_view_number = TYPE_READ_REMOTE_POINT_INFO;
            //Tstat_Window->m_tstat_list.SetFocus();
            //bacnet_view_number = TYPE_TSTAT;
            //g_hwnd_now = m_tstat_dlg_hwnd;
        }
        if(ScreenEdit_Window)
        {
            ::SendMessage(m_screen_dlg_hwnd,WM_SCREENEDIT_CLOSE,NULL,NULL);
        }
        ((CBacnetProgram*)pDialog[WINDOW_PROGRAM])->Unreg_Hotkey();
        ((BacnetScreen*)pDialog[WINDOW_SCREEN])->Unreg_Hotkey();
        ((BacnetWeeklyRoutine*)pDialog[WINDOW_WEEKLY])->Unreg_Hotkey();
        ((BacnetAnnualRoutine*)pDialog[WINDOW_ANNUAL])->Unreg_Hotkey();
        ((CBacnetMonitor*)pDialog[WINDOW_MONITOR])->Unreg_Hotkey();

        if(bac_select_device_online)
            ::PostMessage(BacNet_hwd,WM_FRESH_CM_LIST,MENU_CLICK,TYPE_READ_REMOTE_POINT_INFO);
        //else
        //	MessageBox(_T("Device is Offline ,Please Check the connection!"),_T("Warning"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {

        MessageBox(_T("This function only support bacnet protocol!\r\nPlease select a bacnet product first."));
    }


    bacnet_view_number = TYPE_TSTAT ;
}


void CMainFrame::ShowDebugWindow()
{
    if(DebugWindow == NULL)
    {
        DebugWindow = new CDebugWindow;
        DebugWindow->Create(IDD_DIALOG_DEBUG_TRACE, this);
        DebugWindow->ShowWindow(SW_HIDE);
        g_Print = _T("Debug Time 15-05-28   Debug version 2.4");
        DFTrace(g_Print);
    }

    if(DebugWindow->IsWindowVisible())
    {
        enable_show_debug_window = false;
        DebugWindow->ShowWindow(SW_HIDE);
    }
    else
        DebugWindow->ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateConnect2(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_nStyle == 1);
}


//建立TCP 服务器, GSM 会连接上来;
void CMainFrame::OnMiscellaneousGsmconnection()
{
    // TODO: Add your command handler code here

    if(Tcp_Server_Window == NULL)
    {
        Tcp_Server_Window = new CTCP_Server;
        Tcp_Server_Window->Create(IDD_GSM_SERVER, this);
        Tcp_Server_Window->ShowWindow(SW_SHOW);
    }
    else
    {
        Tcp_Server_Window->ShowWindow(SW_SHOW);
    }

    return;

}


UINT _PingThread(LPVOID pParam)
{
    CMainFrame* pDlg = (CMainFrame*)(pParam);
    CString strIP = pDlg->m_strPingIP;
    Ping(strIP, pDlg);
    return 1;
}
//Ping
void CMainFrame::OnTestPing(const CString& strIP)
{
    m_strPingIP = strIP;
    AfxBeginThread(_PingThread, this);
}

//
void CMainFrame::BuildingComportConfig()
{
    CADO ado;
    ado.OnInitADOConn();
    bool n_building_port = false;
    if(m_subNetLst.size()<=0)
    {
        n_building_port = false;
    }
    else
    {
        CString comport = m_subNetLst.at(0).strComPort;
        if(comport.GetLength()<=3)
        {
            n_building_port = false;
        }
        else
        {
            if(comport.Left(3).CompareNoCase(_T("COM")) == 0)
            {
                CString temp_i_port;
                temp_i_port = comport.Right(comport.GetLength() - 3);
                m_building_com_port = _wtoi(temp_i_port);


                GetSerialComPortNumber1(m_vector_comport);
                if(m_vector_comport.size()>0)
                {
                    bool find_comport = false;
                    for (int j=0; j<m_vector_comport.size(); j++)
                    {
                        if(comport.CompareNoCase(m_vector_comport.at(j)) == 0)
                        {
                            open_com(m_building_com_port);
                            find_comport = true;
                            break;
                        }
                    }

                    if(find_comport)
                    {
                        SetLastOpenedComport(m_building_com_port);
                        open_com(m_building_com_port);
                    }
                    else	//如果在枚举的 串口里面没有找到就默认第一个;还要改数据库;
                    {
                        CString temp_port;
                        temp_port = m_vector_comport.at(0);
                        temp_port = temp_port.Right(temp_port.GetLength() - 3);
                        m_building_com_port = _wtoi(temp_port);



                        try
                        {

                            CString strSql;
                            strSql.Format(_T("update Building set Com_Port='%s' where Building_Name='%s' and Main_BuildingName='%s'"),m_vector_comport.at(0),m_strCurSubBuldingName,m_strCurMainBuildingName);


                            ado.m_pConnection->Execute(strSql.GetString(),NULL,adCmdText);


                            m_subNetLst.at(0).strComPort = m_vector_comport.at(0);
                        }
                        catch (...)
                        {

                        }

                    }


                }


            }
        }
    }

    ado.CloseConn();
}


BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
    // TODO: Add your message handler code here and/or call default
    int nSize = pCopyDataStruct->cbData;// = (strMsg.GetLength()+1)*sizeof(TCHAR); //(lstrlen(szBuffer)+1)*sizeof(TCHAR);
    //pCopyDataStruct->lpData =  (LPVOID)(LPCTSTR)strMsg;
    CString strMsg = CString(LPCTSTR(pCopyDataStruct->lpData));

    //CListBox* pList = (CListBox*)GetDlgItem(IDC_LIST_INFO);
    //pList->AddString(strMsg);
    CString show_info;
    show_info.Format(_T("Ping - "));
    show_info = show_info + strMsg;
    SetPaneString(BAC_SHOW_MISSION_RESULTS,show_info);
    //UpdateStatusInfo(strMsg, FALSE);
    //UpdateData(TRUE);
    return CFrameWndEx::OnCopyData(pWnd, pCopyDataStruct);
    /*return CDialog::OnCopyData(pWnd, pCopyDataStruct);*/
}


void CMainFrame::OnUpdateDisconnect2(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_nStyle == 2);
}
void CMainFrame::OnUpdateScanDevice(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_nStyle == 3);
}
void CMainFrame::OnUpdateAddBuildingConfig(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_nStyle ==4);
}

void CMainFrame::OnUpdateStatusBar(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(TRUE);

}
#include "MailFeedbackDlg.h"
void CMainFrame::OnHelpFeedbacktotemco()
{
    m_product_isp_auto_flash.baudrate = m_product.at(selected_product_index).baudrate;
    m_product_isp_auto_flash.BuildingInfo.strIp = m_product.at(selected_product_index).BuildingInfo.strIp;
    m_product_isp_auto_flash.ncomport =  m_product.at(selected_product_index).ncomport;

    m_product_isp_auto_flash.product_class_id =  m_product.at(selected_product_index).product_class_id;
    m_product_isp_auto_flash.product_id =  m_product.at(selected_product_index).product_id;


    Dowmloadfile Dlg;
    Dlg.DoModal();


// 	 CMailFeedbackDlg dlg;
// 	 dlg.DoModal();
// 	CString m_strWebLinker;
// 	m_strWebLinker.Format(_T("mailto:alex@temcocontrols.com?subject=feedback to temco &body=please add the attachment in the \n%sT3000.log "),g_strExePth);
// 	try{
// 		ShellExecute(GetSafeHwnd(), NULL,m_strWebLinker,   NULL, NULL,   SW_SHOWNORMAL);
// 	}
// 	catch(...)
// 	{
// 		AfxMessageBox(_T("Error:Can't find the email client in your pc!"));
// 	}




//
// 	int ModelID=_wtoi(_T("6"));
// 	GetProductFPTAndLocalPath(ModelID,m_sURLToDownload,ProductName);
//
// 	m_sFileToDownloadInto = g_strExePth;
// 	m_sFileToDownloadInto+=_T("firmware\\");
// 	CreateDirectory(m_sFileToDownloadInto,NULL);
// 	StrTemp.Format(_T("%s\\"),GetProductName(ModelID));
// 	m_sFileToDownloadInto+=StrTemp;
// 	CreateDirectory(m_sFileToDownloadInto,NULL);
// 	m_sFileToDownloadInto+=ProductName;
// 	DownloadFromFTP();
}


CString CMainFrame::GetFWVersionFromFTP(CString ProductName)
{
    CString strHtml("");
    CInternetSession sess;
    CHttpFile* pHttpFile = NULL;
    CString ULR("http://temcocontrols.com/ftp/firmware/FV.txt");

    pHttpFile = (CHttpFile*)sess.OpenURL(ULR.GetBuffer());

    char sRecived[1024];
    if(pHttpFile)
    {
        while(pHttpFile->ReadString((LPTSTR)sRecived, 1024)) //解决Cstring乱码
        {
            CString temp(sRecived);
            /*	strHtml += temp;* /*/
            CStringArray  stringarray;
            SplitCStringA(stringarray,temp,_T("="));
            CString scourceProductName=stringarray[0];
            if (scourceProductName.CompareNoCase(ProductName.GetBuffer())==0)
            {
                strHtml=stringarray[1];
                break;
            }
        }
    }
    return strHtml;

}

//-----------------------------------------------------------------------------

LRESULT CMainFrame::OnThreadFinished(WPARAM wParam, LPARAM /*lParam*/)
{



    //If an error occured display the message box

    if (wParam)
    {
        /*AfxMessageBox(m_sError);*/
        //EndDialog(IDCANCEL);
        m_bSafeToClose=TRUE;
        return 0L;
    }
    //下载完成之后，打开文件
    else
    {
        //EndDialog(IDOK);
        m_bSafeToClose=TRUE;

        //Free up the internet handles we may be using
        if (m_hHttpFile)
        {
            ::InternetCloseHandle(m_hHttpFile);
            m_hHttpFile = NULL;
        }
        if (m_hHttpConnection)
        {
            ::InternetCloseHandle(m_hHttpConnection);
            m_hHttpConnection = NULL;
        }
        if (m_hInternetSession)
        {
            ::InternetCloseHandle(m_hInternetSession);
            m_hInternetSession = NULL;

        }
        AfxMessageBox(_T("Finished"));
        return 1L;
    }
    return 0L;
}

UINT CMainFrame::_DownloadThread(LPVOID pParam)
{
    //Convert from the SDK world to the C++ world
    return 0;
    CMainFrame* pDlg =(CMainFrame*) pParam;
    ASSERT(pDlg);
    ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CMainFrame)));
    pDlg->DownloadAllThread();
    return 0;
}

BOOL CMainFrame::DownloadThread()
{
    //Create the Internet session handle
    ASSERT(m_hInternetSession == NULL);
    m_hInternetSession = ::InternetOpen(AfxGetAppName(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (m_hInternetSession == NULL)
    {
        TRACE(_T("Failed in call to InternetOpen, Error:%d\n"), ::GetLastError());
        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_GENERIC_ERROR);
        m_bSafeToClose=TRUE;
        return FALSE;
    }

    //Should we exit the thread


    //Setup the status callback function
    if (::InternetSetStatusCallback(m_hInternetSession, _OnStatusCallBack) == INTERNET_INVALID_STATUS_CALLBACK)
    {
        TRACE(_T("Failed in call to InternetSetStatusCallback, Error:%d\n"), ::GetLastError());
        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_GENERIC_ERROR);
        m_bSafeToClose=TRUE;
        return FALSE;;
    }

    //Should we exit the thread


    //Make the connection to the HTTP server
    ASSERT(m_hHttpConnection == NULL);
    if (m_sUserName.GetLength())
        m_hHttpConnection = ::InternetConnect(m_hInternetSession, m_sServer, m_nPort, m_sUserName,
                                              m_sPassword, m_dwServiceType, 0, (DWORD) this);
    else
        m_hHttpConnection = ::InternetConnect(m_hInternetSession, m_sServer, m_nPort, NULL,
                                              NULL, m_dwServiceType, 0, (DWORD) this);
    if (m_hHttpConnection == NULL)
    {
        TRACE(_T("Failed in call to InternetConnect, Error:%d\n"), ::GetLastError());
        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
        m_bSafeToClose=TRUE;
        return FALSE;;
    }

    //Should we exit the thread


    //Start the animation to signify that the download is taking place


    //Issue the request to read the file
    LPCTSTR ppszAcceptTypes[2];
    ppszAcceptTypes[0] = _T("*/*");  //We support accepting any mime file type since this is a simple download of a file
    ppszAcceptTypes[1] = NULL;
    ASSERT(m_hHttpFile == NULL);
    m_hHttpFile = HttpOpenRequest(m_hHttpConnection, NULL, m_sObject, NULL, NULL, ppszAcceptTypes, INTERNET_FLAG_RELOAD |
                                  INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION, (DWORD) this);
    if (m_hHttpFile == NULL)
    {
        TRACE(_T("Failed in call to HttpOpenRequest, Error:%d\n"), ::GetLastError());
        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
        m_bSafeToClose=TRUE;
        return FALSE;
    }

    //Should we exit the thread


//label used to jump to if we need to resend the request
resend:

    //Issue the request
    BOOL bSend = ::HttpSendRequest(m_hHttpFile, NULL, 0, NULL, 0);
    if (!bSend)
    {
        TRACE(_T("Failed in call to HttpSendRequest, Error:%d\n"), ::GetLastError());
        HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_FAIL_CONNECT_SERVER);
        m_bSafeToClose=TRUE;
        return FALSE;
    }

    //Check the HTTP status code
    TCHAR szStatusCode[32];
    DWORD dwInfoSize = 32;
    if (!HttpQueryInfo(m_hHttpFile, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwInfoSize, NULL))
    {
        TRACE(_T("Failed in call to HttpQueryInfo for HTTP query status code, Error:%d\n"), ::GetLastError());
        HandleThreadError(IDS_HTTPDOWNLOAD_INVALID_SERVER_RESPONSE);
        m_bSafeToClose=TRUE;
        return FALSE;
    }
    else
    {
        long nStatusCode = _ttol(szStatusCode);

        //Handle any authentication errors
        if (nStatusCode == HTTP_STATUS_PROXY_AUTH_REQ || nStatusCode == HTTP_STATUS_DENIED)
        {
            // We have to read all outstanding data on the Internet handle
            // before we can resubmit request. Just discard the data.
            char szData[51];
            DWORD dwSize;
            do
            {
                ::InternetReadFile(m_hHttpFile, (LPVOID)szData, 50, &dwSize);
            }
            while (dwSize != 0);

            //Bring up the standard authentication dialog
            if (::InternetErrorDlg(GetSafeHwnd(), m_hHttpFile, ERROR_INTERNET_INCORRECT_PASSWORD, FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
                                   FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, NULL) == ERROR_INTERNET_FORCE_RETRY)
                goto resend;
        }
        else if (nStatusCode != HTTP_STATUS_OK)
        {
            TRACE(_T("Failed to retrieve a HTTP 200 status, Status Code:%d\n"), nStatusCode);
            HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_INVALID_HTTP_RESPONSE, nStatusCode);
            m_bSafeToClose=TRUE;
            return FALSE;
        }
    }

    //Update the status control to reflect that we are getting the file information
    //SetStatus(IDS_HTTPDOWNLOAD_GETTING_FILE_INFORMATION);

    // Get the length of the file.
    TCHAR szContentLength[32];
    dwInfoSize = 32;
    DWORD dwFileSize = 0;
    BOOL bGotFileSize = FALSE;
    if (::HttpQueryInfo(m_hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szContentLength, &dwInfoSize, NULL))
    {
        //Set the progress control range
        bGotFileSize = TRUE;
        dwFileSize = (DWORD) _ttol(szContentLength);
        //SetProgressRange(dwFileSize);
    }

    //Update the status to say that we are now downloading the file
    //SetStatus(IDS_HTTPDOWNLOAD_RETREIVEING_FILE);

    //Now do the actual read of the file
    DWORD dwStartTicks = ::GetTickCount();
    DWORD dwCurrentTicks = dwStartTicks;
    DWORD dwBytesRead = 0;
    char szReadBuf[1024];
    DWORD dwBytesToRead = 1024;
    DWORD dwTotalBytesRead = 0;
    DWORD dwLastTotalBytes = 0;
    DWORD dwLastPercentage = 0;
    do
    {
        if (!::InternetReadFile(m_hHttpFile, szReadBuf, dwBytesToRead, &dwBytesRead))
        {
            TRACE(_T("Failed in call to InternetReadFile, Error:%d\n"), ::GetLastError());
            HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_ERROR_READFILE);
            m_bSafeToClose=TRUE;
            return FALSE;
        }
        else if (dwBytesRead)
        {
            //Write the data to file
            TRY
            {
                m_FileToWrite.Write(szReadBuf, dwBytesRead);
            }
            CATCH(CFileException, e);
            {
                TRACE(_T("An exception occured while writing to the download file\n"));
                HandleThreadErrorWithLastError(IDS_HTTPDOWNLOAD_ERROR_READFILE, e->m_lOsError);
                e->Delete();
                m_bSafeToClose=TRUE;
                return FALSE;
            }
            END_CATCH

            //Increment the total number of bytes read
            dwTotalBytesRead += dwBytesRead;


        }
    }
    while (dwBytesRead);

    //Delete the file being downloaded to if it is present and the download was aborted
    m_FileToWrite.Close();
    //We're finished
    m_bSafeToClose=TRUE;
    return TRUE;
// PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED);
}

#define CLOSE_HANDLE(handle) \
	do \
	 { \
	 CloseHandle(handle); \
	 handle = NULL; \
} while (FALSE)

void CMainFrame::DownloadAllThread()
{
    CString StrTemp;
    CString ProductHexBinName;
    CString WebFileSize;
    CString ProductName;
    //CADO ado;
    //ado.OnInitADOConn();
    CBADO bado;
    bado.SetDBPath(g_strCurBuildingDatabasefilePath);
    bado.OnInitADOConn();

    CString strSql;
    strSql=_T("select  distinct Product_class_ID from ALL_NODE");
    bado.m_pRecordset=bado.OpenRecordset(strSql);
    //ado.m_pRecordset->MoveFirst();
    while(!bado.m_pRecordset->EndOfFile)
    {
        if(m_bSafeToClose)
        {

            if (m_hHttpFile)
            {
                ::InternetCloseHandle(m_hHttpFile);
                m_hHttpFile = NULL;
            }
            if (m_hHttpConnection)
            {
                ::InternetCloseHandle(m_hHttpConnection);
                m_hHttpConnection = NULL;
            }
            if (m_hInternetSession)
            {
                ::InternetCloseHandle(m_hInternetSession);
                m_hInternetSession = NULL;

            }


            StrTemp=bado.m_pRecordset->GetCollect(_T("Product_class_ID"));
            int ModelID=_wtoi(StrTemp);
            GetProductFPTAndLocalPath(ModelID,m_sURLToDownload,ProductHexBinName);
            CString StrTips=_T("");
            CString StrBinHexPath;
            CString ProductFirmwareTime,ProductFirmwareSize,WebProductFirmwareTime;
            CString FirmwareDirectoryURL,FirmwareName;
            GetProductFirmwareFTPDirectory(ModelID,FirmwareDirectoryURL,FirmwareName);
            ProductName=GetProductName(ModelID);
            WebProductFirmwareTime=GetProductFirmwareTimeFromTemcoWebsite(FirmwareDirectoryURL,FirmwareName,WebFileSize);
            StrBinHexPath = g_strExePth;
            StrBinHexPath+=_T("firmware\\");

            StrTemp.Format(_T("%s\\"),ProductName);
            //m_file_firmware_Size
            GetPrivateProfileStringW(_T("Setting"),ProductName+_T("-Time"),_T(""),ProductFirmwareTime.GetBuffer(MAX_PATH),MAX_PATH,m_file_firmware_Time);
            GetPrivateProfileStringW(_T("Setting"),ProductName+_T("-Size"),_T(""),ProductFirmwareSize.GetBuffer(MAX_PATH),MAX_PATH,m_file_firmware_Time);
            StrBinHexPath+=StrTemp;
            StrBinHexPath+=ProductHexBinName;

            HANDLE hFind;//
            WIN32_FIND_DATA wfd;//
            hFind = FindFirstFile(StrBinHexPath, &wfd);//


//			HANDLE hFile = ::CreateFile(StrBinHexPath, GENERIC_READ | FILE_SHARE_READ, 0,
//				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//			if (hFile!= INVALID_HANDLE_VALUE)
//			{
//				//_tprintf_s(_T("Failed to create file handle: %s ! error code:%d\n"), szFileName, GetLastError());
//				//return -1;
//
//				UINT64 uFileSize = 0;
//				::GetFileSizeEx(hFile, reinterpret_cast<PLARGE_INTEGER>(&uFileSize));
//
//				FILE_STANDARD_INFO fsi = {0};
//				if (!::GetFileInformationByHandleEx(hFile, FileStandardInfo, &fsi, sizeof(FILE_STANDARD_INFO)))
//				{
//					_tprintf_s(_T("Failed to get file info! error code:%d\n"), GetLastError());
//					CLOSE_HANDLE(hFile);
//					return -1;
//				}
//
//// 				_tprintf_s(_T("FileName : %s\n"), szFileName);
//// 				_tprintf_s(_T("FileSize : %I64u Byte\n"), uFileSize);
//// 				_tprintf_s(_T("FileSpacesSize : %I64u Byte\n"), fsi.AllocationSize);
//                ProductFirmwareSize.Format(_T("%0.1fK"),uFileSize/1024);
//				CLOSE_HANDLE(hFile);
//
//			}



            if (hFind!=INVALID_HANDLE_VALUE)
            {
                DWORD nfilesize=wfd.nFileSizeLow;
                if (nfilesize<1024*1024)
                {
                    ProductFirmwareSize.Format(_T("%0.1fK"),nfilesize/1024);
                }

            }

            if (((WebProductFirmwareTime.CompareNoCase(ProductFirmwareTime)!=0)&&(!m_sURLToDownload.IsEmpty()))||(hFind==INVALID_HANDLE_VALUE))//说明当前目录下无t3000.mdb
            {
                if (!m_sURLToDownload.IsEmpty())
                {
                    //WritePrivateProfileStringW(_T("Setting"),_T("DB_IPADDRESS"),_T("192.168.0.202"),SettingPath);
                    WritePrivateProfileStringW(_T("Setting"),ProductName+_T("-Time"),WebProductFirmwareTime,m_file_firmware_Time);
                    WritePrivateProfileStringW(_T("Setting"),ProductName+_T("-Size"),WebFileSize,m_file_firmware_Time);
                    //SetPaneString(3,GetProductName(ModelID));
                    m_sFileToDownloadInto = g_strExePth;
                    m_sFileToDownloadInto+=_T("firmware\\");
                    CreateDirectory(m_sFileToDownloadInto,NULL);
                    StrTemp.Format(_T("%s\\"),GetProductName(ModelID));
                    StrTips.Format(_T("%s's frimware is downloading....."),GetProductName(ModelID));
                    CString* pstrInfo = new CString(StrTips);
                    ::SendMessage(this->m_hWnd,WM_SHOW_PANNELINFOR,WPARAM(pstrInfo),LPARAM(3));

                    m_sFileToDownloadInto+=StrTemp;
                    CreateDirectory(m_sFileToDownloadInto,NULL);
                    m_sFileToDownloadInto+=ProductHexBinName;
                    m_bSafeToClose=FALSE;
                    DownloadFromFTP();
                    Sleep(15000);
                }
            }



            bado.m_pRecordset->MoveNext();
        }
        else
        {
            Sleep(20000);
            continue;
        }
    }
    bado.CloseConn();
}
void CMainFrame::HandleThreadErrorWithLastError(UINT nIDError, DWORD dwLastError)
{
    //Form the error string to report
    CString sError;
    if (dwLastError)
        sError.Format(_T("%d"), dwLastError);
    else
        sError.Format(_T("%d"), ::GetLastError());
    AfxFormatString1(m_sError, nIDError, sError);

    //Delete the file being downloaded to if it is present
    m_FileToWrite.Close();
    ::DeleteFile(m_sFileToDownloadInto);

    //PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED, 1);
}

void CMainFrame::HandleThreadError(UINT nIDError)
{
    m_sError.LoadString(nIDError);
    //PostMessage(WM_HTTPDOWNLOAD_THREAD_FINISHED, 1);
}

void CALLBACK CMainFrame  ::_OnStatusCallBack(HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus,
        LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
    //Convert from the SDK C world to the C++ world
    CMainFrame  * pDlg = (CMainFrame  *) dwContext;
    ASSERT(pDlg);
    ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CMainFrame  )));
    //pDlg->OnStatusCallBack(hInternet, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
}

void CMainFrame  ::OnStatusCallBack(HINTERNET /*hInternet*/, DWORD dwInternetStatus,
                                    LPVOID lpvStatusInformation, DWORD /*dwStatusInformationLength*/)
{
    switch (dwInternetStatus)
    {
    case INTERNET_STATUS_RESOLVING_NAME:
    {
        //SetStatus(IDS_HTTPDOWNLOAD_RESOLVING_NAME, (LPCTSTR) lpvStatusInformation);
        break;
    }
    case INTERNET_STATUS_NAME_RESOLVED:
    {
        //SetStatus(IDS_HTTPDOWNLOAD_RESOLVED_NAME, (LPCTSTR) lpvStatusInformation);
        break;
    }
    case INTERNET_STATUS_CONNECTING_TO_SERVER:
    {
        //SetStatus(IDS_HTTPDOWNLOAD_CONNECTING, (LPCTSTR) lpvStatusInformation);
        break;
    }
    case INTERNET_STATUS_CONNECTED_TO_SERVER:
    {
        //SetStatus(IDS_HTTPDOWNLOAD_CONNECTED, (LPCTSTR) lpvStatusInformation);
        break;
    }
    case INTERNET_STATUS_REDIRECT:
    {
        //SetStatus(IDS_HTTPDOWNLOAD_REDIRECTING, (LPCTSTR) lpvStatusInformation);
        break;
    }
    default:
    {
        break;
    }
    }
}

BOOL CMainFrame::DownloadFromFTP()
{

    ASSERT(m_sURLToDownload.GetLength()); //Did you forget to specify the file to download
    if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
    {
        //Try sticking "http://" before it
        m_sURLToDownload = _T("http://") + m_sURLToDownload;
        if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
        {
            m_bSafeToClose=TRUE;
            return FALSE;

        }
    }
    //Check to see if the file we are downloading to exists and if
    //it does, then ask the user if they were it overwritten
    CFileStatus fs;
    ASSERT(m_sFileToDownloadInto.GetLength());
    if (CFile::GetStatus(m_sFileToDownloadInto, fs))
    {

    }
    //Try and open the file we will download into
    if (!m_FileToWrite.Open(m_sFileToDownloadInto, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
    {
        TRACE(_T("Failed to open the file to download into, Error:%d\n"), GetLastError());
        CString sError;
        sError.Format(_T("%d"), ::GetLastError());
        CString sMsg;
        AfxFormatString1(sMsg, IDS_HTTPDOWNLOAD_FAIL_FILE_OPEN, sError);
        //AfxMessageBox(sMsg);
        //EndDialog(IDCANCEL);
        m_bSafeToClose=TRUE;
        return FALSE;
    }

    //Pull out just the filename component
    int nSlash = m_sObject.ReverseFind(_T('/'));
    if (nSlash == -1)
        nSlash = m_sObject.ReverseFind(_T('\\'));
    if (nSlash != -1 && m_sObject.GetLength() > 1)
        m_sFilename = m_sObject.Right(m_sObject.GetLength() - nSlash - 1);
    else
        m_sFilename = m_sObject;

    //Set the file status text
    CString sFileStatus;
    ASSERT(m_sObject.GetLength());
    ASSERT(m_sServer.GetLength());
    AfxFormatString2(sFileStatus, IDS_HTTPDOWNLOAD_FILESTATUS, m_sFilename, m_sServer);

    return DownloadThread();
}
void CMainFrame::GetProductFPTAndLocalPath(int ProductModel,CString &FtpPath,CString &ProductFileName)
{
    CString strProductName;
    switch(ProductModel)
    {
    case PM_TSTAT5A:
        strProductName="TStat5A";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5B:
        strProductName="TStat5B";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5B2:
        strProductName="TStat5B2";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5C:
        strProductName="TStat5C";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5D:
        strProductName="TStat5D";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5E:
        strProductName="TStat5E";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5F:
        strProductName="TStat5F";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5G:
        strProductName="TStat5G";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }

        break;
    case PM_TSTAT5H:
        strProductName="TStat5H";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }

        break;
    case PM_TSTAT6:
        strProductName="TStat6";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/Tstat6/128kChip/TSTAT6.HEX");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5i:
        strProductName="TStat5i";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_HUMTEMPSENSOR:
        strProductName="TstatHUM";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_AirQuality:
        strProductName="Air Quality";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT7:
        strProductName="TStat7";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_NC:
        strProductName="NC";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_CM5:
        strProductName ="CM5";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTATRUNAR:
        strProductName="TStatRunar";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    //20120424
    case PM_LightingController:
        strProductName = "LC";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case  PM_CO2_NET:
        strProductName = "CO2 Net";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/CO2/CO2-W-E/CO2-W-E.bin");
            ProductFileName=_T("CO2-Ethernet.bin");
        }
        break;
    case  PM_CO2_RS485:
        strProductName = "CO2";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/CO2/CO2-W/CO2-W.hex");
            ProductFileName=_T("CO2-RS485.HEX");
        }
        break;
    case PM_TSTAT6_HUM_Chamber:
        strProductName =g_strHumChamber;
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;

    case PM_T3PT10 :
        strProductName="T3-PT10";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T3IOA :
        strProductName="T3-8IOA";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T332AI :
        strProductName="T3-32AI";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case  PM_T38AI16O :
        strProductName="T3-8AI160";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T38I13O :
        strProductName="T3-8I13O";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T3PERFORMANCE :
        strProductName="T3-Performance";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T34AO :
        strProductName="T3-4AO";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T36CT :
        strProductName="T3-6CT";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_MINIPANEL:
        strProductName="MiniPanel";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_PRESSURE:
        strProductName="Pressure Sensor";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_HUM_R:
        strProductName="HUM-R";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    default:
        strProductName="TStat";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    }
}

void CMainFrame::GetProductFirmwareFTPDirectory(int ProductModel,CString &FtpPath,CString &ProductFileName)
{
    CString strProductName;
    switch(ProductModel)
    {
    case PM_TSTAT5A:
        strProductName="TStat5A";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5B:
        strProductName="TStat5B";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5B2:
        strProductName="TStat5B2";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5C:
        strProductName="TStat5C";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5D:
        strProductName="TStat5D";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5E:
        strProductName="TStat5E";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5F:
        strProductName="TStat5F";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT5G:
        strProductName="TStat5G";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }

        break;
    case PM_TSTAT5H:
        strProductName="TStat5H";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }

        break;
    case PM_TSTAT6:
        strProductName="TStat6";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/Tstat6/128kChip/");
            ProductFileName=_T("TSTAT6.HEX");
        }
        break;
    case PM_TSTAT5i:
        strProductName="TStat5i";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_HUMTEMPSENSOR:
        strProductName="TstatHUM";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_AirQuality:
        strProductName="Air Quality";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTAT7:
        strProductName="TStat7";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_NC:
        strProductName="NC";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_CM5:
        strProductName ="CM5";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_TSTATRUNAR:
        strProductName="TStatRunar";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    //20120424
    case PM_LightingController:
        strProductName = "LC";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case  PM_CO2_NET:
        strProductName = "CO2 Net";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/CO2/CO2-W-E/");
            ProductFileName=_T("CO2-W-E.bin");
        }
        break;
    case  PM_CO2_RS485:
        strProductName = "CO2";
        {
            FtpPath=_T("http://temcocontrols.com/ftp/firmware/CO2/CO2-W/");
            ProductFileName=_T("CO2-W.hex");
        }
        break;
    case PM_TSTAT6_HUM_Chamber:
        strProductName =g_strHumChamber;
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;

    case PM_T3PT10 :
        strProductName="T3-PT10";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T3IOA :
        strProductName="T3-8IOA";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T332AI :
        strProductName="T3-32AI";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case  PM_T38AI16O :
        strProductName="T3-8AI160";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T38I13O :
        strProductName="T3-8I13O";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T3PERFORMANCE :
        strProductName="T3-Performance";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T34AO :
        strProductName="T3-4AO";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_T36CT :
        strProductName="T3-6CT";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_MINIPANEL:
        strProductName="MiniPanel";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_PRESSURE:
        strProductName="Pressure Sensor";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    case PM_HUM_R:
        strProductName="HUM-R";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    default:
        strProductName="TStat";
        {
            FtpPath=_T("");
            ProductFileName=_T("Tstat6.HEX");
        }
        break;
    }
}
#include "DetectOnlineDlg.h"
void CMainFrame::OnToolDetectonlineproducts()
{
    CLoginDlg Dlg(g_buser_log_in);
    if (Dlg.DoModal()==IDOK)
    {
        CDetectOnlineDlg dlg;
        dlg.DoModal();
    }



}


void CMainFrame::OnUpdateControlMain(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_MAIN);
}


void CMainFrame::OnUpdateControlInputs(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_INPUT);

//       if(pCmdUI->m_pMenu != NULL)
//       {
//           pCmdUI->SetText(L"TEST INPUT");
//       }

}

void CMainFrame::OnUpdateControlOutputs(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_OUTPUT);
}


void CMainFrame::OnUpdateControlVariables(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_VARIABLE);
}


void CMainFrame::OnUpdateControlPrograms(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_PROGRAM);
}


void CMainFrame::OnUpdateControlScreens(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_SCREENS);
}


void CMainFrame::OnUpdateControlControllers(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_CONTROLLER);
}


void CMainFrame::OnUpdateControlWeekly(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_WEEKLY);
}


void CMainFrame::OnUpdateControlAnnualroutines(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_ANNUAL);
}


void CMainFrame::OnUpdateControlMonitors(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_MONITOR);
}


void CMainFrame::OnUpdateControlAlarmLog(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_ALARMLOG);
}

void CMainFrame::Create_Thread_Read_Item(int n_item)
{
    if(WaitRead_Data_Dlg)
    {
        delete WaitRead_Data_Dlg;
        WaitRead_Data_Dlg = 0;
    }
    WaitRead_Data_Dlg = new CDialog_Progess(this,1,100);
    //创建对话框窗口
    WaitRead_Data_Dlg->Create(IDD_DIALOG10_Progress, this);
    WaitRead_Data_Dlg->ShowProgress(0,0);
    RECT RECT_SET1;
    ::GetWindowRect(BacNet_hwd,&RECT_SET1);
    WaitRead_Data_Dlg->MoveWindow(RECT_SET1.left + 50,RECT_SET1.bottom - 19,800,20,1);
    WaitRead_Data_Dlg->ShowWindow(SW_HIDE);
    g_bac_read_type = n_item;
    if(click_read_thread==NULL)
    {
        click_read_thread =CreateThread(NULL,NULL,MSTP_Send_read_Command_Thread,this,NULL, NULL);
    }
}

void CMainFrame::OnUpdateControlTstat(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_TSTAT);
}


void CMainFrame::OnUpdateControlSettings(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(bacnet_view_number == TYPE_SETTING);
}


BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo)
{
    // TODO: Add your message handler code here and/or call default   IDH_TOPIC_TBS_COVER_EDITOR
    HWND hWnd;

    if(pHelpInfo->dwContextId > 0) hWnd = ::HtmlHelp((HWND)pHelpInfo->hItemHandle, theApp.m_szHelpFile, HH_HELP_CONTEXT, pHelpInfo->dwContextId);
    else
        hWnd =  ::HtmlHelp((HWND)pHelpInfo->hItemHandle, theApp.m_szHelpFile, HH_HELP_CONTEXT, IDH_TOPIC_OVERVIEW);

    return (hWnd != NULL);
    return CFrameWndEx::OnHelpInfo(pHelpInfo);
}

void CMainFrame::OnFileExportregiseterslist()
{
    CStdioFile* m_pFile;


    CString  Product_Head_File_Name;
    CString strFilter;
    CString strFilename;
    CString strTemp;
    CString RegisterName;
    CString RegisterID;
    CString logstr;
    _variant_t  temp_variant;

    BOOL IS_Write=TRUE;
    m_pFile = new CStdioFile;//txt
    CString HeadFold = g_strExePth;

    HeadFold += _T("Product Head File");
    CreateDirectory(HeadFold,NULL);

    Product_Head_File_Name =HeadFold;

    _Application app;
    Workbooks books;
    _Workbook book;
    Worksheets sheets;
    _Worksheet sheet;
    Range range;
    Range rgMyRge1, rgMyRge2;
    COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

    strFilename=g_strExePth+_T("ModbusBacnetRegistersList.xls");
    if(!app.CreateDispatch(_T("Excel.Application"),NULL))
    {
        AfxMessageBox(_T("Create Excel false!"));
        return;
    }
    books.AttachDispatch(app.GetWorkbooks());
    book.AttachDispatch(books.Add(_variant_t(strFilename)));
    sheets.AttachDispatch(book.GetWorksheets());





    //CS3000
#if 1


    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\CS3000.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//CS3000 Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();

    sheet.AttachDispatch(sheets.GetItem(_variant_t("CS3000")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    int Rows=2;
    CADO ado;
    ado.OnInitADOConn();
    CString StrSql;
    StrSql=_T("Select * from CS3000 ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    int RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {

        temp_variant=ado.m_pRecordset->GetCollect("RegName");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }



        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;



        temp_variant=ado.m_pRecordset->GetCollect("RegDiscription");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }



        Rows++;

        ado.m_pRecordset->MoveNext();

    }
    m_pFile->Flush();
    m_pFile->Close();
    ado.CloseRecordset();
#endif




    //AQ
#if 1

    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\Air Quanlity.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//AQ Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();


    sheet.AttachDispatch(sheets.GetItem(_variant_t("Air Quality")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from AirQuanlity_Reglist ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));

        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("RegName");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));

        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }


        temp_variant=ado.m_pRecordset->GetCollect("RegFullDescription");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }


        ado.m_pRecordset->MoveNext();

    }

    m_pFile->Flush();
    m_pFile->Close();


    ado.CloseRecordset();


#endif

    //T3 Modules
#if 1
    CString Str_T3_8AI8AO , Str_T3_8AI16O, Str_T3_8I13O, Str_T3_32AI,Str_T3_4AO, Str_T3_6CT, Str_T3_28IN, Str_T3_PT10;

    CStdioFile* m_pFile_8AI8AO = new CStdioFile;
    CStdioFile* m_pFile_8AI16O = new CStdioFile;
    CStdioFile* m_pFile_8I13O  = new CStdioFile;
    CStdioFile* m_pFile_32AI   = new CStdioFile;
    CStdioFile* m_pFile_6CT    = new CStdioFile;
    CStdioFile* m_pFile_28IN   = new CStdioFile;
    CStdioFile* m_pFile_PT10   = new CStdioFile;
    CStdioFile* m_pFile_4AO    = new CStdioFile;

    Str_T3_8AI8AO   = HeadFold+ _T("\\T3_8AI8AO.h");
    Str_T3_8AI16O	= HeadFold+ _T("\\T3_8AI16O.h");
    Str_T3_8I13O	= HeadFold+ _T("\\T3_8I13O.h");
    Str_T3_32AI		= HeadFold+ _T("\\T3_32AI.h");
    Str_T3_6CT		= HeadFold+ _T("\\T3_6CT.h");
    Str_T3_28IN		= HeadFold+ _T("\\T3_28IN.h");
    Str_T3_PT10		= HeadFold+ _T("\\T3_PT10.h");
    Str_T3_4AO      = HeadFold+ _T("\\T3_4AO.h");
    //m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_8AI8AO->Open(Str_T3_8AI8AO.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_8AI16O->Open(Str_T3_8AI16O.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_8I13O->Open(Str_T3_8I13O.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_32AI->Open(Str_T3_32AI.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_6CT->Open(Str_T3_6CT.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_28IN->Open(Str_T3_28IN.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_PT10->Open(Str_T3_PT10.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_4AO->Open(Str_T3_4AO.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//8AI8AO Head \n");
    m_pFile_8AI8AO->SeekToEnd();
    m_pFile_8AI8AO->WriteString(logstr.GetBuffer());
    m_pFile_8AI8AO->WriteString(_T("\n"));
    m_pFile_8AI8AO->Flush();

    logstr=_T("");
    logstr=_T("//8AI16O Head \n");
    m_pFile_8AI16O->SeekToEnd();
    m_pFile_8AI16O->WriteString(logstr.GetBuffer());
    m_pFile_8AI16O->WriteString(_T("\n"));
    m_pFile_8AI16O->Flush();

    logstr=_T("");
    logstr=_T("//8I13O Head \n");
    m_pFile_8I13O->SeekToEnd();
    m_pFile_8I13O->WriteString(logstr.GetBuffer());
    m_pFile_8I13O->WriteString(_T("\n"));
    m_pFile_8I13O->Flush();

    logstr=_T("");
    logstr=_T("//32AI Head \n");
    m_pFile_32AI->SeekToEnd();
    m_pFile_32AI->WriteString(logstr.GetBuffer());
    m_pFile_32AI->WriteString(_T("\n"));
    m_pFile_32AI->Flush();

    logstr=_T("");
    logstr=_T("//6CT Head \n");
    m_pFile_6CT->SeekToEnd();
    m_pFile_6CT->WriteString(logstr.GetBuffer());
    m_pFile_6CT->WriteString(_T("\n"));
    m_pFile_6CT->Flush();

    logstr=_T("");
    logstr=_T("//28IN Head \n");
    m_pFile_28IN->SeekToEnd();
    m_pFile_28IN->WriteString(logstr.GetBuffer());
    m_pFile_28IN->WriteString(_T("\n"));
    m_pFile_28IN->Flush();

    logstr=_T("");
    logstr=_T("//PT10 Head \n");
    m_pFile_PT10->SeekToEnd();
    m_pFile_PT10->WriteString(logstr.GetBuffer());
    m_pFile_PT10->WriteString(_T("\n"));
    m_pFile_PT10->Flush();

    logstr=_T("");
    logstr=_T("//4AO Head \n");
    m_pFile_4AO->SeekToEnd();
    m_pFile_4AO->WriteString(logstr.GetBuffer());
    m_pFile_4AO->WriteString(_T("\n"));
    m_pFile_4AO->Flush();



    sheet.AttachDispatch(sheets.GetItem(_variant_t("T3 Modules")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("T3-8AI8AO")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("T3-8AI8AO Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(4)),_variant_t(_T("T3-8AI16O")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(5)),_variant_t(_T("T3-8AI16O Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(6)),_variant_t(_T("T3-8I13O")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(7)),_variant_t(_T("T3-8I13O Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(8)),_variant_t(_T("T3-32AI")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(9)),_variant_t(_T("T3-32AI Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(10)),_variant_t(_T("T3-32AI")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(11)),_variant_t(_T("T3-32AI Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(12)),_variant_t(_T("T3-6CT")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(13)),_variant_t(_T("T3-6CT Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(14)),_variant_t(_T("T3-28IN")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(15)),_variant_t(_T("T3-28IN Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(16)),_variant_t(_T("T3-PT10")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(17)),_variant_t(_T("T3-PT10 Description")));
    Rows=2;


    StrSql=_T("Select * from T3_RegisterList ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("T3-8AI8AO");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_8AI8AO->SeekToEnd();
            m_pFile_8AI8AO->WriteString(logstr.GetBuffer());
        }

        temp_variant=ado.m_pRecordset->GetCollect("T3-8AI8AO_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));



        temp_variant=ado.m_pRecordset->GetCollect("T3-8AI16O");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(4)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_8AI16O->SeekToEnd();
            m_pFile_8AI16O->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("T3-8AI16O_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(5)),_variant_t(strTemp));


        temp_variant=ado.m_pRecordset->GetCollect("T3-8I13O");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(6)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_8I13O ->SeekToEnd();
            m_pFile_8I13O ->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("T3-8I13O_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(7)),_variant_t(strTemp));

        temp_variant=ado.m_pRecordset->GetCollect("T3-32AI");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(8)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_32AI->SeekToEnd();
            m_pFile_32AI->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("T3-32AI_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(9)),_variant_t(strTemp));

        temp_variant=ado.m_pRecordset->GetCollect("T3-4AO");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(10)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_4AO->SeekToEnd();
            m_pFile_4AO->WriteString(logstr.GetBuffer());
        }

        temp_variant=ado.m_pRecordset->GetCollect("T3-4AO_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(11)),_variant_t(strTemp));


        temp_variant=ado.m_pRecordset->GetCollect("T3-6CT");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(12)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_6CT->SeekToEnd();
            m_pFile_6CT->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("T3-6CT_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(13)),_variant_t(strTemp));


        temp_variant=ado.m_pRecordset->GetCollect("T3-28IN");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(14)),_variant_t(strTemp));

        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_28IN->SeekToEnd();
            m_pFile_28IN->WriteString(logstr.GetBuffer());
        }

        temp_variant=ado.m_pRecordset->GetCollect("T3-28IN_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(15)),_variant_t(strTemp));


        temp_variant=ado.m_pRecordset->GetCollect("T3-RTD");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(16)),_variant_t(strTemp));

        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_PT10->SeekToEnd();
            m_pFile_PT10->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("T3-RTD_DESCRIPTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(17)),_variant_t(strTemp));




        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    ado.CloseRecordset();

    m_pFile_8AI8AO->Flush();
    m_pFile_8AI16O->Flush();
    m_pFile_8I13O->Flush();
    m_pFile_32AI->Flush();
    m_pFile_6CT->Flush();
    m_pFile_28IN->Flush();
    m_pFile_PT10->Flush();
    m_pFile_4AO->Flush();

    m_pFile_8AI8AO->Close();
    m_pFile_8AI16O->Close();
    m_pFile_8I13O->Close();
    m_pFile_32AI->Close();
    m_pFile_6CT->Close();
    m_pFile_28IN->Close();
    m_pFile_PT10->Close();
    m_pFile_4AO->Close();


    delete m_pFile_8AI8AO;
    delete m_pFile_8AI16O;
    delete m_pFile_8I13O;
    delete m_pFile_32AI;
    delete m_pFile_6CT;
    delete m_pFile_28IN;
    delete m_pFile_PT10;
    delete m_pFile_4AO;



#endif

    //Pressure Sensor
#if 1
    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\Pressure Sensor.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//Pressure Sensor Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();

    sheet.AttachDispatch(sheets.GetItem(_variant_t("Pressure Sensor")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from PS_Registerlist ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("Reg_Name");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("Reg_FulDescription");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    m_pFile->Flush();
    m_pFile->Close();
    ado.CloseRecordset();
#endif

    //MiniPanel
#if 1

    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\MiniPanel.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//MiniPanel Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();

    sheet.AttachDispatch(sheets.GetItem(_variant_t("MiniPanel")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from MiniPanel_Registerlist ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("Reg_Name");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));

        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if(IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }

        temp_variant=ado.m_pRecordset->GetCollect("Register_Description");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    m_pFile->Flush();
    m_pFile->Close();

    ado.CloseRecordset();
#endif

    //Humidity_Sensor
#if 1
    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\Humidity Sensor.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//Humidity Sensor Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();

    sheet.AttachDispatch(sheets.GetItem(_variant_t("Humidity Sensor")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from Humidity_Sensor ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp ;

        temp_variant=ado.m_pRecordset->GetCollect("Reg_Name");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));

        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("Reg_Full_Description");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }
    m_pFile->Flush();
    m_pFile->Close();
    ado.CloseRecordset();
#endif
//Tstat5
#if 1


    CString Str_Tstat5LED , Str_Tstat5LCD;
    CStdioFile* m_pFile_Tstat5LED = new CStdioFile;
    CStdioFile* m_pFile_Tstat5LCD = new CStdioFile;

    Str_Tstat5LED   = HeadFold+ _T("\\Tstat5LED.h");
    Str_Tstat5LCD	= HeadFold+ _T("\\Tstat5LCD.h");

    m_pFile_Tstat5LED->Open(Str_Tstat5LED.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );
    m_pFile_Tstat5LCD->Open(Str_Tstat5LCD.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );


    logstr=_T("");
    logstr=_T("//Tstat5 LED Head \n");
    m_pFile_Tstat5LED->SeekToEnd();
    m_pFile_Tstat5LED->WriteString(logstr.GetBuffer());
    m_pFile_Tstat5LED->WriteString(_T("\n"));
    m_pFile_Tstat5LED->Flush();

    logstr=_T("");
    logstr=_T("//Tstat5 LCD Head \n");
    m_pFile_Tstat5LCD->SeekToEnd();
    m_pFile_Tstat5LCD->WriteString(logstr.GetBuffer());
    m_pFile_Tstat5LCD->WriteString(_T("\n"));
    m_pFile_Tstat5LCD->Flush();


    sheet.AttachDispatch(sheets.GetItem(_variant_t("Tstat5LED&&Tstat5LCD")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("TSTAT5LED AddressName")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("TSTAT5LED Description")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(4)),_variant_t(_T("TSTAT5LCD AddressName")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(5)),_variant_t(_T("TSTAT5LCD Description")));
    Rows=2;


    StrSql=_T("Select * from T3000_Register_Address_By_ID ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("Register_Address");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("TSTAT5_LED_AddressName");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_Tstat5LCD->SeekToEnd();
            m_pFile_Tstat5LCD->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("TSTAT5_LED_INSTRUCTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        temp_variant=ado.m_pRecordset->GetCollect("TSTAT5_LCD_AddressName");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(4)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile_Tstat5LED->SeekToEnd();
            m_pFile_Tstat5LED->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("TSTAT5_LCD_INSTRUCTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(5)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    m_pFile_Tstat5LCD->Flush();
    m_pFile_Tstat5LCD->Close();
    delete m_pFile_Tstat5LCD;

    m_pFile_Tstat5LED->Flush();
    m_pFile_Tstat5LED->Close();
    delete m_pFile_Tstat5LED;

    ado.CloseRecordset();
#endif
    //Tstat 5 I-6-7
#if 1

    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\Tstat5I_6_7.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//Tstat5I_6_7 Head \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();


    sheet.AttachDispatch(sheets.GetItem(_variant_t("Tstat5I&&Tstat6&&Tstat7")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from T3000_Register_Address_By_ID ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("Register_Address");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));

        RegisterID = strTemp;

        temp_variant=ado.m_pRecordset->GetCollect("TSTAT6_AddressName");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }

        temp_variant=ado.m_pRecordset->GetCollect("TSTAT6_INSTRUCTION");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    m_pFile->Flush();
    m_pFile->Close();

    ado.CloseRecordset();
#endif

    //CO2-W
#if 1

    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\CO2_W.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//CO2 W \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();


    sheet.AttachDispatch(sheets.GetItem(_variant_t("CO2-W")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from CO2RS485RegList ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));

        RegisterID = strTemp ;

        temp_variant=ado.m_pRecordset->GetCollect("485_Name_V3");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("485_INSTRUCTION_V3");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }

    m_pFile->Flush();
    m_pFile->Close();

    ado.CloseRecordset();
#endif

    //CO2-W+Ethernet
#if 1

    Product_Head_File_Name=_T("");
    //Product_Head_File_Name = HeadFold;
    Product_Head_File_Name   = HeadFold+ _T("\\CO2_Ethernet.h");

    m_pFile->Open(Product_Head_File_Name.GetString(),CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeCreate );

    logstr=_T("");
    logstr=_T("//CO2  Ethernet \n");
    m_pFile->SeekToEnd();
    m_pFile->WriteString(logstr.GetBuffer());
    m_pFile->WriteString(_T("\n"));
    m_pFile->Flush();


    sheet.AttachDispatch(sheets.GetItem(_variant_t("CO2-W+Ethernet")));
    range.AttachDispatch(sheet.GetCells());
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(_T("Address")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t(_T("Register Name")));
    range.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t(_T("Register Description")));
    Rows=2;


    StrSql=_T("Select * from CO2NETRegList ");
    ado.m_pRecordset = ado.OpenRecordset(StrSql);
    RecordCount=ado.GetRecordCount(ado.m_pRecordset);
    ado.m_pRecordset->MoveFirst();
    while(!ado.m_pRecordset->EndOfFile)
    {
        temp_variant=ado.m_pRecordset->GetCollect("RegID");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(1)),_variant_t(strTemp));
        RegisterID = strTemp;
        temp_variant=ado.m_pRecordset->GetCollect("NET_Name");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(2)),_variant_t(strTemp));
        strTemp.TrimRight();
        strTemp.TrimLeft();
        if (strTemp.CompareNoCase(_T("RESERVED"))!=0&&!strTemp.IsEmpty())
        {
            IS_Write = TRUE ;
            RegisterName = strTemp;
        }
        else
        {
            IS_Write = FALSE ;
        }

        if (IS_Write)
        {
            logstr.Format(_T("#define  %s  %s \n"),RegisterName,RegisterID);
            m_pFile->SeekToEnd();
            m_pFile->WriteString(logstr.GetBuffer());
        }


        temp_variant=ado.m_pRecordset->GetCollect("NET_Description");//
        if(temp_variant.vt!=VT_NULL)
            strTemp=temp_variant;
        else
        {
            strTemp=_T("");
        }
        range.SetItem(_variant_t((long)(Rows)),_variant_t((long)(3)),_variant_t(strTemp));

        Rows++;

        ado.m_pRecordset->MoveNext();

    }
    m_pFile->Flush();

    ado.CloseRecordset();
#endif


    m_pFile->Close();
    delete m_pFile;

    ado.CloseConn();
    app.SetVisible(true);
    range.ReleaseDispatch();
    sheet.ReleaseDispatch();
    sheets.ReleaseDispatch();
    book.ReleaseDispatch();
    books.ReleaseDispatch();
    app.ReleaseDispatch();
}


//void CMainFrame::OnToolProductsregistersmaintenance()
//{
//    CString strHistotyFile=g_strExePth+_T("RegisterListManager.exe");
//    ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
//}


void CMainFrame::OnToolRegistersmaintenancesystem()
{
    //维护寄存器列表管理的 一个应用程序
    //它能够维护所以产品的寄存器
    // 它的所有的功能列表
    /*
    1>用户管理
    2>密码修改
    3>项目管理
    4>寄存器信息修改
    5>产品的添加
    */
    CString strHistotyFile=g_strExePth+_T("RegisterListManager.exe");
    ShellExecute(NULL, _T("open"), strHistotyFile, NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMainFrame::OnToolTipNotify(UINT id,NMHDR *Pnmhdr,LRESULT *pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *) Pnmhdr;

    UINT_PTR nID = Pnmhdr->idFrom - 1;

    if (Pnmhdr->hwndFrom == m_testtoolbar.Get_Tip_HWND())
    {
        CMFCToolBarButton *pBtn = m_testtoolbar.GetButton(nID);
        if (pBtn)
        {
            if(pBtn->m_nID ==  ID_CONTROL_MAIN)
            {
                pTTT->lpszText = _T("Information \r\nMore information about the device");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_INPUTS)
            {
                pTTT->lpszText = _T("Inputs [ Alt-I ]\r\nSensors and feedback points wired to the controller");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_OUTPUTS)
            {
                pTTT->lpszText = _T("Outputs [ Alt-O ]\r\nValves, relays and actuators wired to the controller");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_VARIABLES)
            {
                pTTT->lpszText = _T("Variables [ Alt-V ]\r\nSetpoints, counters, timers and other system defined items");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_PROGRAMS)
            {
                pTTT->lpszText = _T("Programs [ Alt-P ]\r\nSystem logic and sequencing");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_CONTROLLERS)
            {
                pTTT->lpszText = _T("PID Loops [ Alt-L ]\r\nProportional-Integral-Derivative feedback control loops");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_SCREENS)
            {
                pTTT->lpszText = _T("Graphics [ Alt-G ]\r\nFloor plans, system diagrams, graphical displays");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_WEEKLY)
            {
                pTTT->lpszText = _T("Schedules [ Alt-S ]\r\nDaily on and off events for the week");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_ANNUALROUTINES)
            {
                pTTT->lpszText = _T("Holidays [ Alt-H ]\r\nHolidays and days with special schedules during the year");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_MONITORS)
            {
                pTTT->lpszText = _T("Trend Logs [ Alt-T ]\r\nGraphs and historical data");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_ALARM_LOG)
            {
                pTTT->lpszText = _T("Alarms [ Alt-A ]\r\nCurrent and past alarm events");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_TSTAT)
            {
                pTTT->lpszText = _T("Network Points[ Alt-N ]\r\nNetwork points from other nodes used by the controller");
            }
            else if(pBtn->m_nID ==  ID_CONTROL_SETTINGS)
            {
                pTTT->lpszText = _T("Configuration [ Alt-C ]\r\nSetup and advanced parameters");
            }
            else if(pBtn->m_nID ==  ID_SCAN)
            {
                pTTT->lpszText = _T("Discover [Alt-D]\r\nDiscover new devices on the LAN, com ports and USB");
            }
            else if(pBtn->m_nID ==  ID_BUILDINGCONFIGDB)
            {
                pTTT->lpszText = _T("Buildings [Alt-B]\r\nDatabase of all buildings, connect to a different site or go offline to set up a new one");
            }

            pTTT->hinst = AfxGetResourceHandle();
        }
    }

    return true;

}







INT_PTR CMainFrame::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
    // TODO: Add your specialized code here and/or call the base class

    return CFrameWndEx::OnToolHitTest(point, pTI);


    CString adoStr;
    static CString strText;
    INT_PTR hInt = CFrameWndEx::OnToolHitTest(point,pTI);//先调用基类函数,再修改串.   ;
    strText = pTI->lpszText;

    //if(pTI->uId == ID_CONTROL_INPUTS )
    //{
    //	adoStr = _T("test111");

    //}
    strText = adoStr + strText; //重新组合成: New(Ctrl+N)形式.

    //基类中会释放这个指针pTI->lpszText,但是由于我们要修改这个串,
    //所以原来的空间不一定够,所以要释放掉原来的,并重新申请,
    int len = strText.GetLength()*sizeof(TCHAR);
    TCHAR *pBuf =(TCHAR*)malloc(len+10);
    memset(pBuf,0,len+10);
    _tcscpy_s(pBuf,strText.GetLength()+2,strText);
    free(pTI->lpszText);
    pTI->lpszText = pBuf;

    return hInt;

}

#include "BatchSNDlg.h"
void CMainFrame::OnToolFlashsn()
{
    g_bPauseMultiRead =TRUE;
    CBatchSNDlg dlg;
    dlg.DoModal();
    g_bPauseMultiRead =FALSE;
}


void CMainFrame::OnMove(int x, int y)
{
    CFrameWndEx::OnMove(x, y);

    // TODO: Add your message handler code here
    if(b_create_status)
    {
        CRect temprec;
        m_wndStatusBar.GetWindowRect(&temprec);
        if((temprec.top >0) && (temprec.bottom >0) && (temprec.left >0) && (temprec.right > 0))
            statusbar->SetWindowPos(&wndTop,temprec.left,temprec.top,temprec.Width(),temprec.Height(),SWP_NOACTIVATE | SWP_SHOWWINDOW );

    }
}
