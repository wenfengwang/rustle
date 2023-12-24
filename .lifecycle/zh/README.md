# Rustle

<img src="./logo.png" alt="Rustle" width="500"/>

[![CI 状态](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![构建映像状态](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![许可证：AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/Honorable%20Mention-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle 是 NEAR 智能合约在 Rust 中的自动静态分析器。它可以帮助定位 NEAR 智能合约中的数十种不同的漏洞。
根据 [DefiLlama](https://defillama.com/chain/Near) 的数据，在 NEAR 的前 10 个 DApp 中，有 8 个经过 BlockSec 的审计。凭借丰富的审计经验和对 NEAR 协议的深刻理解，我们构建了这个工具并与社区分享。

## 入门

### 先决条件

#### Linux 设置

在 Linux 中，使用以下命令为 **Rustle** 安装所需的工具包。这些命令已在 Ubuntu 20.04 LTS 中进行了测试。

```bash
# 安装 Rust 工具链
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 安装 LLVM 15
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# 安装 Python 工具链
sudo apt install python3 python3-pip    # 需要 python >= 3.8
pip3 install -r utils/requirements.txt  # 需要先克隆此存储库

# 添加 WASM 目标
rustup target add wasm32-unknown-unknown

# 安装其他组件
sudo apt install figlet
cargo install rustfilt

# [可选] 开发中有用的工具
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOS 设置

以下命令适用于 macOS 用户，它们仅在 Apple Silicon Mac 上进行了测试，因此请谨慎使用。

```bash
# 安装 Rust 工具链
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 安装 LLVM 15
brew install llvm@15

# 安装 Python 包
pip3 install -r utils/requirements.txt  # 需要先克隆此存储库
                                        # 使用 macOS 默认的 python3

# 添加 WASM 目标
rustup target add wasm32-unknown-unknown

# 安装其他组件
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

我们提供了一个 Docker 解决方案。

```bash
# 构建镜像
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# 从镜像运行容器
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# 执行容器
docker start rustle
docker exec -it -w /rustle rustle bash
```

### 用法

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`：合约源的路径。
* `tg_dir`：合约构建目标的路径。默认为与 `src_dir` 相同。
* `detector`：检测器列表。可以用于传递多个*检测器*或*组*，用`,`分隔。默认为 `all`。
    * 传递 `all` *组* 以启用所有检测器。
    * 传递 `high`、 `medium`、 `low` 和 `info` *组* 以启用具有不同严重性的检测器组（参见[检测器](#detectors)）
    * 传递 `nep-ft`、 `nep-storage` 和 `nep-nft` *组* 以启用为指定 NEP 实现的检测器（参见[NEP 检测器组](#nep-detector-groups)）
    * 通过[表](#detectors)中的*检测器 ID* 以启用这些检测器
* `output`：将生成审计报告的路径。默认为 `./audit-result`。

注意：如果由 cargo 构建的目标位码（`.bc` 二进制）不在 `$src_dir` 中，则使用 `-t|--tg_dir` 设置目标的目录，否则默认为 `$src_dir`。

下面的命令显示了分析 LiNEAR 的示例。

```bash
# 克隆 LiNEAR
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# 运行 Rustle
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [可选] 在指定的检测器或严重性组上运行 Rustle，并将审计报告保存在 `~/linear-report` 中
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

CSV 格式的报告将在目录“./audit-result”中生成。

## 检测器

**Rustle** 可以找到的所有漏洞。

| 检测器 ID             | 描述                                                                                 | 严重性 |
| ----------------------- | ------------------------------------------------------------------------------------------- | -------- |
| `unhandled-promise`     | [查找未处理的 `Promises`](docs/detectors/unhandled-promise.md)                 | 高     |
| `non-private-callback`  | [回调函数缺少宏 `#[private]`](docs/detectors/non-private-callback.md) | 高     |
| `reentrancy`            | [查找易受重入攻击的函数](docs/detectors/reentrancy.md)     | 高     |
| `unsafe-math`           | [算术运算缺乏溢出检查](docs/detectors/unsafe-math.md)            | 高     |
| `self-transfer`         | [缺少对 `sender != receiver` 的检查](docs/detectors/self-transfer.md)                    | 高     |
| `incorrect-json-type`   | [参数或返回值中使用的类型不正确](docs/detectors/incorrect-json-type.md) | 高     |
| `unsaved-changes`       | [未保存对集合的更改](docs/detectors/unsaved-changes.md)                   | 高     |
| `nft-approval-check`    | [查找 `nft_transfer` 时未检查 `approval id`](docs/detectors/nft-approval-check.md)  | 高     |
| `nft-owner-check`       | [查找未对所有者进行检查的批准或撤销功能](docs/detectors/nft-owner-check.md)   | 高     |
| `div-before-mul`        | [由于操作顺序不正确导致的精度损失](docs/detectors/div-before-mul.md)         | 中等   |
| `round`                 | [舍入时未指定 ceil 或 floor](docs/detectors/round.md)                        | 中等   |
| `lock-callback`         | [回调函数中可能会锁定合约](docs/detectors/lock-callback.md)             | 中等   |
| `yocto-attach`          | [特权函数中缺少 `assert_one_yocto`](docs/detectors/yocto-attach.md)              | 中等   |
| `dup-collection-id`     | [集合中使用重复的 ID](docs/detectors/dup-collection-id.md)                     | 中等   |
| `unregistered-receiver` | [未在未注册的转账接收者上触发 panic](docs/detectors/unregistered-receiver.md)      | 中等   |
| `nep${id}-interface`    | [查找所有未实现的 NEP 接口](docs/detectors/nep-interface.md)                     | 中等   |
| `prepaid-gas`           | [在 `ft_transfer_call` 中缺少预付 gas 的检查](docs/detectors/prepaid-gas.md)         | 低      |
| `non-callback-private`  | [在非回调函数中使用了宏 `#[private]`](docs/detectors/non-callback-private.md)  | 低      |
| `unused-ret`            | [未使用或检查函数结果](docs/detectors/unused-ret.md)                         | 低      |
| `upgrade-func`          | [合约中缺少升级函数](docs/detectors/upgrade-func.md)                           | 低      |
| `tautology`             | [在条件分支中使用了重言式](docs/detectors/tautology.md)                         | 低      |
| `storage-gas`           | [存储扩展时缺少余额检查](docs/detectors/storage-gas.md)                | 低      |
| `unclaimed-storage-fee` | [在存储注销之前缺少余额检查](docs/detectors/unclaimed-storage-fee.md)  | 低      |
| `inconsistency`         | [使用了类似但略有不同的符号](docs/detectors/inconsistency.md)             | 信息     |
| `timestamp`             | [查找所有 `timestamp` 的用法](docs/detectors/timestamp.md)                                 | 信息     |
| `complex-loop`          | [查找所有具有复杂逻辑的循环，可能导致 DoS](docs/detectors/complex-loop.md)   | 信息     |
| `ext-call`              | [查找所有跨合约调用](docs/detectors/ext-call.md)                           | 信息     |
| `promise-result`        | [查找所有 promise 结果的用法](docs/detectors/promise-result.md)                         | 信息     |
| `transfer`              | [查找所有转账操作](docs/detectors/transfer.md)                                     | 信息     |
| `public-interface`      | [查找所有公共接口](docs/detectors/public-interface.md)                            | 信息     |

### NEP 检测器组

除了按严重性级别分组外，**Rustle** 还提供了一些按相应 NEP 划分的检测器组。目前，**Rustle** 支持以下组。

[NEP141]: https://github.com/near/NEPs/blob/master/neps/nep-0141.md
[NEP145]: https://github.com/near/NEPs/blob/master/neps/nep-0145.md
[NEP171]: https://github.com/near/NEPs/blob/master/neps/nep-0171.md
[NEP178]: https://github.com/near/NEPs/blob/master/neps/nep-0178.md

| NEP                                  | 检测器组 ID | 检测器 ID                                                 |
| ------------------------------------ | ----------------- | ------------------------------------------------------------ |
| [NEP-141][NEP141]                    | `nep-ft`          | `nep141-interface`, `self-transfer`, `unregistered-receiver` |
| [NEP-145][NEP145]                    | `nep-storage`     | `nep145-interface`, `unclaimed-storage-fee`                  |
| [NEP-171][NEP171], [NEP-178][NEP178] | `nep-nft`         | `nep171-interface`, `nft-approval-check`, `nft-owner-check`  |

## 添加新检测器

1. 将此存储库分叉到您的帐户。
2. 将新的检测器放在 [/detectors](/detectors/) 目录下。
3. 在 [/Makefile](/Makefile) 中添加一个检测目标，其中包含运行您的检测器的命令。
4. 将目标添加到 `audit` 目标的依赖项中，并将其名称添加到 `./rustle` 脚本中的[检测器列表](/rustle#L146)和[严重性组](/rustle#L169)。
5. 在 [/utils/audit.py](/utils/audit.py) 中添加处理代码（参考其他检测器的 `audit.py` 中的代码）。
6. 从您的分支向主分支提交拉取请求。

## 注意
**Rustle** 可以在开发过程中用于迭代扫描 NEAR 智能合约。这可以节省大量的手动工作并减轻部分潜在问题。然而，复杂逻辑中的漏洞或与语义相关的漏洞仍然是 **Rustle** 的局限性。要定位复杂的语义问题，需要 [BlockSec](https://blocksec.com/) 的专家进行彻底和全面的审查。请通过 [联系我们](audit@blocksec.com) 获取审核服务。

## 许可证

该项目采用 AGPLv3 许可证。请参阅 [LICENSE](LICENSE) 文件获取完整的许可文本。