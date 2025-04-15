/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "string.h"
#include "stdlib.h"
#include "midi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Адрес страницы, куда будут сохраняться структуры
#define flashADDR   0x08022000
/*----------------------------------------------------------------------------*/
// Тестовая структура для записи
struct
{
	uint8_t  var1;
	uint16_t var2;
	uint32_t var3;
	double   var4;
} test_struct;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI3_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void shift_reg_init(){
	HAL_GPIO_WritePin(MR_GPIO_Port, MR_Pin, 1);
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, 0);
}

void put_val_to_shift_reg(uint16_t val){
	int c = 0;
	while(c < 16){
		HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, val & 1);
		val >>= 1;
		HAL_GPIO_WritePin(CLK1_GPIO_Port, CLK1_Pin, 1);
		HAL_GPIO_WritePin(CLK1_GPIO_Port, CLK1_Pin, 0);
		c++;
	}
	HAL_GPIO_WritePin(CLK2_GPIO_Port, CLK2_Pin, 1);
	HAL_GPIO_WritePin(CLK2_GPIO_Port, CLK2_Pin, 0);
}

void clear_shift_reg(){
	HAL_GPIO_WritePin(MR_GPIO_Port, MR_Pin, 0);
	HAL_GPIO_WritePin(MR_GPIO_Port, MR_Pin, 1);

	HAL_GPIO_WritePin(CLK2_GPIO_Port, CLK2_Pin, 1);
	HAL_GPIO_WritePin(CLK2_GPIO_Port, CLK2_Pin, 0);
}


FATFS fs; // File system
FIL fil; // file
FILINFO finfo;    // File information object
FRESULT fresult; // to store the result
char buffer[1024]; // to store data

UINT br, bw; // file read/write count

/* capacity related variable */

FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

/* to send the data to the uart */

void send_uart (char *string){
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart4, (uint8_t *) string , len, -1); // transmit in blocking mode
}

/* to find the size of data in the buffer */
int bufsize( char *buf){
	int i=0;
	while(*buf++ != '\0') i++;
	return i;
}

void bufclear (void) // clear buffer
{
	for (int i = 0; i < 1024; i++){
		buffer[i] = '\0';
	}
}


void get_sd_dirs(char *path){
	send_uart("READING MEMORY xD \n\r");
	DIR dir;
	char string[128];

	FRESULT res = f_opendir(&dir, path);

	if (res != FR_OK){
		sprintf(string, "res = %d f_opendir\n\r", res);
		send_uart(string);
	}

	if (res == FR_OK)
	{
	  while(1)
	  {
		FILINFO fno;

		res = f_readdir(&dir, &fno);

		if (res != FR_OK){
			sprintf(string, "res = %d f_readdir\n\r", res);
			send_uart(string);
		}

		if ((res != FR_OK) || (fno.fname[0] == 0))
		  break;

		sprintf(string, "%c%c%c%c %10d %s/%s\n\r",
		  ((fno.fattrib & AM_DIR) ? 'D' : '-'),
		  ((fno.fattrib & AM_RDO) ? 'R' : '-'),
		  ((fno.fattrib & AM_SYS) ? 'S' : '-'),
		  ((fno.fattrib & AM_HID) ? 'H' : '-'),
		  (int)fno.fsize, path, fno.fname);

		send_uart(string);
	  }
	}
}


void test_midi_play(){
//    MidiEvent midiEvents[60];

    uint32_t currentTime = 0; // Текущее время в тиках
//	uint8_t baseNote = 60; // Средняя C (C4)
//	uint8_t channel = 0;

	// Массив степеней двойки (2^0, 2^1, ..., 2^8)
//	const uint8_t powerOfTwoNotes[] = {1, 2, 4, 8, 16, 32, 64, 128};
//	const int numNotes = sizeof(powerOfTwoNotes) / sizeof(powerOfTwoNotes[0]);

	// Установим случайный seed для вариативности
//	srand(42); // Можно заменить на time(NULL) для разных последовательностей

//	for (int eventCount = 0; eventCount < 59; eventCount++) {
//		// Случайные параметры ноты (в пределах разумного)
//		uint8_t note = powerOfTwoNotes[rand() % numNotes];
//		uint8_t velocity = 70 + (rand() % 50); // Velocity между 70 и 120
//		uint16_t duration = 100 + (rand() % 400); // Длительность ноты
//		uint16_t pause = 50 + (rand() % 200); // Пауза перед следующей нотой
//
//		// NOTE ON событие
//		midiEvents[eventCount].type = MIDI_NOTE_ON;
//		midiEvents[eventCount].data.note.channel = channel;
//		midiEvents[eventCount].data.note.note = note;
//		midiEvents[eventCount].data.note.velocity = velocity;
//		midiEvents[eventCount].data.note.delta_time = (eventCount == 0) ? 0 : pause; // Первая нота без задержки
//		eventCount++;
//
//		// NOTE OFF событие
//		midiEvents[eventCount].type = MIDI_NOTE_OFF;
//		midiEvents[eventCount].data.note.channel = channel;
//		midiEvents[eventCount].data.note.note = note;
//		midiEvents[eventCount].data.note.velocity = 0;
//		midiEvents[eventCount].data.note.delta_time = duration;
//	}


    FIL file;
    FRESULT res;
    UINT bytesRead, bytesWritten;
	char consoleOutput[128];

    uint8_t fileBuffer[1024];

//    FILE *fileptr;
//	uint8_t *buffer;
//	long filelen;
	MidiEvent midiEvents[100];


	res = f_open(&file, "random.mid", FA_READ);
	if (res != FR_OK) {
		sprintf(consoleOutput, "Ошибка открытия файла: %d\n\r", res);
		send_uart(consoleOutput);
		return;
	}

	int c = 0;

	put_val_to_shift_reg(16);

	while (1) {
		res = f_read(&file, fileBuffer, sizeof(fileBuffer), &bytesRead);

		// Проверяем ошибки и конец файла
		if (res != FR_OK || bytesRead == 0 || c == 1024) {
			break;
		}
		c++;

		// Обрабатываем прочитанные данные
//		send_uart("Прочитано %d байт:\n", bytesRead);
//		for (UINT i = 0; i < bytesRead; i++) {
//			send_uart("%02X ", fileBuffer[i]);
//		}
		send_uart("\n\r");
	}

	// Закрываем файл
	f_close(&file);


//	fileptr = fopen("nggyu.mid", "rb");  // Open the file in binary mode
//	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
//	filelen = ftell(fileptr);             // Get the current byte offset in the file
//	rewind(fileptr);                      // Jump back to the beginning of the file

//	buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
//	fread(buffer, 1, filelen, fileptr); // Read in the entire file
    parse_midi(fileBuffer, 1024, midiEvents, 1024);
    uint16_t output = 0;
    clear_shift_reg();


    for(int i = 0; i < sizeof(midiEvents); i++){
    	currentTime += midiEvents[i].delta_time;

		while (HAL_GetTick() < currentTime) {}

		MidiEvent curEvent = midiEvents[i];
		if (curEvent.type == MIDI_NOTE_ON){
			output = output | (1 << (curEvent.data.note.note % 48));
			put_val_to_shift_reg(output);
			sprintf(consoleOutput, "MIDI NOTE ON = %d ON CHANNEL = %d\n\r", curEvent.data.note.note, curEvent.data.note.channel);
			send_uart(consoleOutput);
			sprintf(consoleOutput, "output = %d\n\r", output);
			send_uart(consoleOutput);

		} else  if(curEvent.type == MIDI_NOTE_OFF){
			if (output > 0)
				output = output & (~(1 << curEvent.data.note.note % 48));
			sprintf(consoleOutput, "MIDI NOTE OFF = %d ON CHANNEL = %d\n\r", curEvent.data.note.note, curEvent.data.note.channel);
			send_uart(consoleOutput);
			put_val_to_shift_reg(output);
			sprintf(consoleOutput, "output = %d\n\r", output);
			send_uart(consoleOutput);
//			clear_shift_reg();
		}
		else if (curEvent.type == MIDI_SET_TEMPO){
			sprintf(consoleOutput, "MIDI SET TEMPO = %d\n\r", curEvent.data.tempo.tempo);
			send_uart(consoleOutput);
		}
		else{
			sprintf(consoleOutput, "%d\n\r", curEvent.type);
			send_uart(consoleOutput);
		}
//		HAL_Delay(1000);
    }
    clear_shift_reg();
}

/**
 * @brief Функция записывает структуру "test_struct" во flash память микроконтроллера
 * @param addr - адрес в памяти микроконтроллера
 * @return статус операции
 */
uint8_t writeFlash (uint32_t addr)
{
//	HAL_StatusTypeDef status;
	uint32_t structureSize = sizeof(test_struct);          // замеряем размер структуры
//	FLASH_EraseInitTypeDef FlashErase;                     // структура для функции стирания страницы
//	uint32_t sectorError = 0;                              // переменная для записи информации об ошибках в процессе стирания

	uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита


	FLASH_Erase_Sector(FLASH_SECTOR_5, FLASH_VOLTAGE_RANGE_1);
	HAL_FLASH_Unlock();                                    // разлочить память

	for (uint8_t i = 0; i < structureSize / 4; i++)
	{
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]) != HAL_OK)
				return 1;
		addr += 4;
	}

	HAL_FLASH_Lock();

	return 0;


//	FlashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
//	FlashErase.NbSectors = 1;
//	FlashErase.Sector = FLASH_SECTOR_5;
//	FlashErase.VoltageRange = VOLTAGE_RANGE_3;
//	if (HAL_FLASHEx_Erase(&FlashErase, &sectorError) != HAL_OK)   // вызов функции стирания
//	{
//		HAL_FLASH_Lock();                                  // если не смог стереть, то закрыть память и вернуть ошибку
//        __enable_irq();
//		return HAL_ERROR;
//	}
//	uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита
//	for (uint8_t i = 0; i < structureSize / 4; i++)
//	{
//		status += HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]);
//		addr += 4;
//	}
//	__enable_irq();                                        // включаем прерывания обратно
//	return status;
}


/*----------------------------------------------------------------------------*/
/**
 * @brief функция считывает значения структуры "test_struct", записанные ранее во flash
 * @param addr - адрес в памяти микроконтроллера
 */
void readFlash (uint32_t addr)
{
	uint32_t structureSize = sizeof(test_struct);
	uint32_t *dataPtr = (uint32_t *)&test_struct;
	for (int i = 0; i < structureSize / 4; i++)
	{
		dataPtr[i] = *(__IO uint32_t*)addr;
		addr += 4;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  shift_reg_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_FATFS_Init();
  MX_SPI3_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  send_uart ("Lift off\n");
  /* Mount SD Card*/
  fresult = f_mount(&fs, "", 0);
  if (fresult != FR_OK) send_uart ("error in mounting SD CARD ... \n");
  else send_uart("SD CARD mounted successfully...\n");

  /* Read dirs from sd card*/
  get_sd_dirs("");
  test_midi_play();

  /* Unmount SDCARD */
  fresult = f_mount(NULL, "/", 1);
  if (fresult == FR_OK) send_uart ("SD CARD UNMOUNTED successfully...\n");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_Delay(1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CLK2_Pin|CLK1_Pin|MR_Pin|DS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OE_Pin */
  GPIO_InitStruct.Pin = OE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CLK2_Pin CLK1_Pin MR_Pin DS_Pin */
  GPIO_InitStruct.Pin = CLK2_Pin|CLK1_Pin|MR_Pin|DS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
