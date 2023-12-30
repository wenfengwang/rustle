
# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![Build-Image Status](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![License: AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle 是一个自动静态分析器，用于 Rust 编写的 NEAR 智能合约。它可以帮助定位 NEAR 智能合约中的数十种不同漏洞。
根据 [DefiLlama](https://defillama.com/chain/Near) 的数据，在 NEAR 的前 10 个 DApp 中，有 8 个经过了 BlockSec 的审计。凭借丰富的审计经验和对 NEAR 协议的深刻理解，我们构建了这个工具并与社区分享。

## 开始使用

### 先决条件

#### Linux 设置

使用以下命令在 Linux 中为 **Rustle** 安装所需的工具包。命令在 Ubuntu 20.04 LTS 中进行了测试。

```bash
# 安装 Rust 工具链
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 安装 LLVM 15
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# 安装 Python 工具链
sudo apt install python3 python3-pip    # 需要 python >= 3.8
pip3 install -r utils/requirements.txt  # 需要先克隆这个仓库

# 添加 WASM 目标
rustup target add wasm32-unknown-unknown

# 安装其他组件
sudo apt install figlet
cargo install rustfilt

# [可选] 开发用的实用工具
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOS 设置

以下命令适用于使用 macOS 的用户，仅在 Apple Silicon Mac 上进行了测试，因此请谨慎使用。

```bash
# 安装 Rust 工具链
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 安装 LLVM 15
brew install llvm@15

# 安装 Python 包
pip3 install -r utils/requirements.txt  # 需要先克隆这个仓库
                                        # 使用 macOS 默认的 python3

# 添加 WASM 目标
rustup target add wasm32-unknown-unknown

# 安装其他组件
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

我们提供了 Docker 解决方案。

```bash
# 构建镜像
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# 从镜像运行容器
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# 执行容器
docker start rustle
docker exec -it -w /rustle rustle bash
```

### 使用方法

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`：合约源代码的路径。
* `tg_dir`：合约构建目标的路径。默认与 `src_dir` 相同。
* `detector`：检测器列表。可以传递多个*检测器*或*组*，用`,`分隔。默认为`all`。
  *   传递 `all` *组*以启用所有检测器。
  *   传递 `high`, `medium`, `low` 和 `info` *组*以启用不同严重程度的检测器组（参考[检测器](#detectors)）
  *   传递 `nep-ft`, `nep-storage` 和 `nep-nft` *组*以启用为特定 NEP 实现的检测器（参考[NEP 检测器组](#nep-detector-groups)）
  *   传递 [表格](#detectors)中的*检测器 ID*以启用这些检测器
* `output`：生成审计报告的路径。默认为 `./audit-result`。

注意：如果由 cargo 构建的目标字节码（`.bc` 二进制文件）不在 `$src_dir` 中，请使用 `-t|--tg_dir` 设置目标的目录，否则将默认设置为 `$src_dir`。

下面的命令展示了分析 LiNEAR 的示例。

```bash
# 克隆 LiNEAR
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# 运行 Rustle
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [可选] 在指定的检测器或严重性组上运行 Rustle 并将审计报告保存在 `~/linear-report`
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

将在目录 `./audit-result` 中生成 CSV 格式的报告。

## 检测器

**Rustle** 能够发现的所有漏洞。

|检测器 ID|描述|严重性|
|---|---|---|
|`unhandled-promise`|查找未处理的 `Promise`|高|
|`non-private-callback`|回调函数缺少宏 `#[private]`|高|
|`reentrancy`|查找易受重入攻击的函数|高|
|`unsafe-math`|缺乏算术运算的溢出检查|高|
|`self-transfer`|缺少 `sender != receiver` 的检查|高|
|`incorrect-json-type`|参数或返回值中使用的类型不正确|高|
|`unsaved-changes`|对集合的更改未被保存|高|
|`nft-approval-check`|查找没有检查 `approval id` 的 `nft_transfer`|高|
|`nft-owner-check`|查找没有进行所有者检查的批准或撤销函数|高|
|`div-before-mul`|由于运算顺序不当导致的精度损失|中|
|`round`|舍入时未指定向上或向下取整|中|
|`lock-callback`|回调函数中的 panic 可能会锁定合约|中|
|`yocto-attach`|特权函数中缺少 `assert_one_yocto`|中|
|`dup-collection-id`|集合中使用了重复的 id|中|
|`unregistered-receiver`|对未注册的传输接收者没有进行 panic|中|
|`nep${id}-interface`|查找所有未实现的 NEP 接口|中|
|`prepaid-gas`|`ft_transfer_call` 中缺少预付燃气检查|低|
|`non-callback-private`|宏 `#[private]` 用于非回调函数|低|
|`unused-ret`|函数结果未被使用或检查|低|
|`upgrade-func`|合约中缺少升级函数|低|
|`tautology`|条件分支中使用了重言式|低|
|`storage-gas`|缺少存储扩展的余额检查|低|
|`unclaimed-storage-fee`|存储注销前缺少余额检查|低|
|`inconsistency`|使用了相似但略有不同的符号|信息|
|`timestamp`|查找所有使用 `timestamp` 的地方|信息|
|`complex-loop`|查找所有可能导致 DoS 的具有复杂逻辑的循环|信息|
|`ext-call`|查找所有跨合约调用|信息|
|`promise-result`|查找所有使用 promise 结果的地方|信息|
|`transfer`|查找所有转账操作|信息|
|`public-interface`|查找所有公共接口|信息|

### NEP 检测器组

除了按严重性级别划分的组外，**Rustle** 还提供了按相应 NEP 划分的检测器组。目前，**Rustle** 支持以下组。


|NEP|检测器组 ID|检测器 ID|
|---|---|---|
|[NEP-141][nep141]|`nep-ft`|`nep141-interface`, `self-transfer`, `unregistered-receiver`|
|[NEP-145][nep145]|`nep-storage`|`nep145-interface`, `unclaimed-storage-fee`|
|[NEP-171][nep171], [NEP-178][nep178]|`nep-nft`|`nep171-interface`, `nft-approval-check`, `nft-owner-check`|

## 添加新检测器

1. 将此仓库 Fork 到您的账户。
2. 将新检测器放在 [/detectors](/detectors/) 下。
3. 在 [/Makefile](/Makefile) 中添加检测目标，并使用命令来运行您的检测器。
4. 将目标添加到 `audit` 目标的依赖项中，并将其名称添加到 `./rustle` 脚本中的[检测器列表](/rustle#L146)和[严重性组](/rustle#L169)中。
5. 在 [utils/audit.py](/utils/audit.py) 中添加处理代码（参考 `audit.py` 中其他检测器的代码）。
6. 从您的分支向主分支提交 Pull Request。

## 注意

**Rustle** 可以在开发过程中用于迭代扫描 NEAR 智能合约。这可以节省大量的手动工作并缓解部分潜在问题。然而，复杂逻辑或与语义相关的漏洞仍然是 **Rustle** 的局限性。定位复杂的语义问题需要 [BlockSec](https://blocksec.com/) 的专家进行详尽和彻底的审查。[联系我们](audit@blocksec.com) 获取审计服务。

## 许可证

该项目采用 AGPLv3 许可证。请参阅 [LICENSE](LICENSE) 文件以获取完整的许可证文本。
