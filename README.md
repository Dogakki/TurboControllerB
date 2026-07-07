# TurboControllerB

涡喷发动机控制系统 — B 板（执行与传感副板）固件

## 概述

B 板是涡喷控制系统中的执行与传感副板，由 A 板主控通过 CAN 总线控制。MCU 为 STM32F412CEU6，运行 FreeRTOS，负责靠近涡喷本体的实时执行器控制和传感器采集。

### 主要功能

| 功能 | 说明 |
|------|------|
| 油泵电机驱动 | DRV8311 三相无刷电调，6 路 PWM (TIM1) |
| 热火头点火 | PWM 功率控制 + INA199 电流检测限流 |
| 阀门控制 | 点火阀 GLOW + 主燃阀 MAIN（低边 N-MOS） |
| 温度采集 | MAX6675 + K 型热电偶，SPI 读取 |
| 转速采集 | KMZ10A 传感器，TIM2 输入捕获 |
| CAN 通信 | 与 A 板双向通信，500kbps |
| 串口调试 | B_TX/B_RX，115200 8N1 |
| 安全保护 | SUB_EN 全局使能、ESC_FAULT、过流、超温保护 |

## 目录结构

```
TurboControllerB/
├── App/                    # 应用层
│   ├── app_init.c/h        # 初始化链: BSP → Components → Services → Modules
│   ├── app_main.c/h        # 主状态机 (9 个状态)
│   └── app_tasks.c/h       # FreeRTOS 任务入口
├── BSP/                    # 板级支持包 (HAL 封装)
│   ├── bsp.c/h             # BSP 初始化聚合
│   ├── bsp_gpio.c/h        # GPIO 读写
│   ├── bsp_can.c/h         # CAN 收发
│   ├── bsp_uart.c/h        # UART 输出
│   ├── bsp_adc.c/h         # ADC DMA + 滤波
│   ├── bsp_pwm.c/h         # PWM (TIM1 CH1-4 + 互补)
│   ├── bsp_spi.c/h         # SPI 接收
│   ├── bsp_tim.c/h         # 定时器输入捕获
│   └── bsp_power.c/h       # ESC_EN / 阀门 / 强制关断
├── Components/             # 外部芯片驱动
│   ├── drv8311/            # DRV8311 ESC 驱动
│   ├── max6675/            # MAX6675 热电偶 IC
│   └── ina199/             # INA199 电流检测
├── Modules/                # 产品功能模块
│   ├── motor/              # 油泵电机控制
│   ├── valve/              # 阀门控制
│   ├── ignition/           # 热火头控制
│   ├── sensor/             # 传感器聚合 + 转速
│   ├── safety/             # 故障检测 + 急停
│   └── sub_enable/         # SUB_EN 监控
├── Services/               # 系统服务
│   ├── service_log.c/h     # 标签化日志
│   ├── service_fault.c/h   # 故障标志管理
│   ├── service_param.c/h   # 参数存储
│   └── service_watchdog.c/h# 软件看门狗
├── Protocol/               # 通信协议
│   ├── protocol_can.c/h    # CAN 消息打包/解析
│   └── protocol_debug.c/h  # 调试 CLI
├── RTOS/                   # FreeRTOS 对象管理
│   ├── rtos.c/h            # RTOS 初始化
│   ├── rtos_tasks.c/h      # 任务创建
│   ├── rtos_queues.c/h     # 队列
│   ├── rtos_events.c/h     # 事件组
│   ├── rtos_mutex.c/h      # 互斥锁
│   └── rtos_timer.c/h      # 软件定时器
├── Config/                 # 配置文件
│   ├── board_config.h      # MCU / 时钟配置
│   ├── pin_config.h        # 引脚定义
│   ├── task_config.h       # 任务栈 / 优先级 / 周期
│   ├── fault_config.h      # 故障阈值
│   └── version.h           # 固件版本
├── Core/                   # CubeMX 生成代码 (不要手动修改)
├── Drivers/                # HAL 驱动 (CubeMX)
├── Middlewares/            # FreeRTOS (CubeMX)
└── CMakeLists.txt
```

## 分层架构

```
┌─────────────────────────────────────────┐
│              App (应用层)                │
│   app_init / app_main / app_tasks       │
├─────────────────────────────────────────┤
│         Modules (功能模块)               │
│   motor / valve / ignition / sensor     │
│   safety / sub_enable                   │
├─────────────────────────────────────────┤
│    Services (服务) + Protocol (协议)     │
│   log / fault / watchdog                │
│   protocol_can / protocol_debug         │
├─────────────────────────────────────────┤
│        Components (芯片驱动)             │
│   drv8311 / max6675 / ina199            │
├─────────────────────────────────────────┤
│            BSP (板级支持)                │
│   gpio / can / uart / adc / pwm         │
│   spi / tim / power                     │
├─────────────────────────────────────────┤
│           Config (配置)                  │
│   board / pin / task / fault / version  │
└─────────────────────────────────────────┘
```

**规则**: 只有 BSP 层调用 `HAL_*` 函数。上层模块通过 BSP API 访问硬件。

## FreeRTOS 任务

| 任务 | 优先级 | 周期 | 职责 |
|------|--------|------|------|
| SafetyTask | Realtime | 5ms | SUB_EN 检查、故障检测、急停 |
| ControlTask | AboveNormal | 10ms | 主状态机执行 |
| MotorTask | AboveNormal | 10ms | 电机控制（预留软启动） |
| CommTask | Normal | 20ms | CAN 收发、协议处理 |
| SensorTask | Normal | 50ms | ADC / 温度 / 转速采集 |
| StorageTask | BelowNormal | 1s | 参数保存 |
| DebugTask | Low | 100ms | 调试命令行 |
| LedTask | Low | 500ms | 状态 LED |

## 状态机

```
DISABLED ──(SUB_EN=HIGH)──> IDLE
                                │
                    (CAN: start)▼
                             PREHEAT
                                │
                  (CAN: ignition)▼
                            IGNITION
                                │
                    (CAN: pump) ▼
                          PUMP_START
                                │
                  (CAN: main)   ▼
                          MAIN_FUEL ──> RUN
                                │          │
                    (CAN: stop) ▼          │ (CAN: pump_target)
                            SHUTDOWN <─────┘
                                │
                                ▼
                              IDLE

任何状态 ──(SUB_EN=LOW / ESC_FAULT / 过流 / 超温)──> FAULT
                                                        │
                                          (CAN: clear)  ▼
                                                        IDLE
```

## 安全机制

### SUB_EN 全局使能

SUB_EN 由 A 板控制，是最高优先级安全信号：

- **SUB_EN = HIGH**: B 板允许执行 CAN 命令
- **SUB_EN = LOW**: B 板必须**立即**关闭所有执行器

SafetyTask 每 5ms 检查 SUB_EN，低电平时：

1. ESC_EN = 0（关闭 DRV8311）
2. 停止 TIM1 所有 PWM
3. IG_PWM = 0（关闭热火头）
4. GLOW = 0（关闭点火阀）
5. MAIN = 0（关闭主燃阀）
6. 忽略所有 CAN 执行类命令

### 故障保护

| 故障 | 触发条件 | 动作 |
|------|----------|------|
| ESC_FAULT | DRV8311 nFAULT 低电平 | 关闭电机 |
| 热火头过流 | INA199 电流 > 阈值 | 关闭 IG_PWM |
| 超温 | MAX6675 温度 > 阈值 | 关闭全部执行器 |
| CAN 超时 | 1s 无有效 CAN 帧 | 进入 FAULT |
| 热电偶开路 | MAX6675 D2=1 | 记录故障 |

## CAN 协议

### A 板 → B 板

| ID | 名称 | 说明 |
|----|------|------|
| 0x100 | 控制命令 | start/stop/ignition/pump/main/clear_fault |
| 0x101 | 手动控制 | 直接控制 IG_PWM/GLOW/MAIN/ESC 使能和占空比 |

### B 板 → A 板

| ID | 名称 | 说明 |
|----|------|------|
| 0x180 | 状态反馈 | 当前状态、故障标志、SUB_EN、ESC_FAULT |
| 0x181 | 传感器数据 | 温度、转速、热火头电流 |
| 0x182 | 电调数据 | 三相电流、油泵占空比 |
| 0x1F0 | 故障上报 | 故障标志、故障时状态 |

## 硬件引脚

### STM32F412CEU6 (UFQFPN48)

| 引脚 | 功能 | 方向 | 说明 |
|------|------|------|------|
| PC13 | SUB_EN | Input | A 板全局使能 |
| PA0 | ESC_FAULT | Input | DRV8311 故障（低有效） |
| PA1 | SPEED | Input | 转速传感器 (TIM2_CH2) |
| PA2 | IGNITION | Output | 点火控制 |
| PA3-PA6 | ADC_IN_A/B/C/GLOW | Analog | 三相电流 + 热火头电流 |
| PA7 | PWM_U_N | PWM | TIM1_CH1N |
| PA8 | PWM_U | PWM | TIM1_CH1 |
| PA9 | PWM_V | PWM | TIM1_CH2 |
| PA10 | PWM_W | PWM | TIM1_CH3 |
| PA11 | IG_PWM | PWM | TIM1_CH4（热火头） |
| PA15 | SPI1_NSS | AF | MAX6675 CS |
| PB0 | PWM_V_N | PWM | TIM1_CH2N |
| PB1 | PWM_W_N | PWM | TIM1_CH3N |
| PB3 | SPI1_SCK | AF | MAX6675 时钟 |
| PB4 | SPI1_MISO | AF | MAX6675 数据 |
| PB5 | ESC_EN | Output | DRV8311 nSLEEP 使能 |
| PB6 | B_TX | AF | USART1_TX 调试 |
| PB7 | B_RX | AF | USART1_RX 调试 |
| PB8 | CAN1_RX | AF | CAN 收发器 |
| PB9 | CAN1_TX | AF | CAN 收发器 |
| PB12 | MAIN | Output | 主燃阀（高有效） |
| PB13 | GLOW | Output | 点火阀（高有效） |

### 时钟配置

| 时钟 | 频率 |
|------|------|
| SYSCLK | 84 MHz (HSI → PLL) |
| HCLK | 42 MHz |
| APB1 | 21 MHz (定时器 42 MHz) |
| APB2 | 42 MHz |

## 构建

### 工具链

- ARM GCC 15.2 (`arm-none-eabi-gcc`)
- CMake 3.22+
- STM32Cube FW_F4 V1.28.3

### 编译

```bash
cmake --preset Debug
cmake --build build/Debug
```

### 产物

- `build/Debug/TurboControllerB.elf` — 调试固件
- `build/Debug/TurboControllerB.hex` — 烧录固件

## 数据流

```
CAN ISR ──(Queue)──> CommTask ──> protocol_can_process_msg()
                                      │
                                      ▼
                                 ControlTask (状态机)
                                      │
                    ┌─────────────────┼─────────────────┐
                    ▼                 ▼                 ▼
               motor_set_duty()  valve_glow_on()  ignition_set_duty()
                    │                 │                 │
                    ▼                 ▼                 ▼
               bsp_pwm_*()      bsp_power_*()     bsp_pwm_*()
                    │                 │                 │
                    ▼                 ▼                 ▼
               HAL_TIM_*()      HAL_GPIO_*()      HAL_TIM_*()


SensorTask ──> sensor_read_all() ──(Mutex)──> sensor_data_t
                    │
         ┌──────────┼──────────┐
         ▼          ▼          ▼
   max6675_read  rpm_get   ina199_get
         │          │          │
         ▼          ▼          ▼
   bsp_spi_*   bsp_tim_*  bsp_adc_*
```

## 版本

- **v1.0.0** — 初始版本，完整框架 + 基础功能

## 许可证

STMicroelectronics HAL 驱动遵循 BSD 许可证。应用代码为私有。
