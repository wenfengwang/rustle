
# 沙沙声

<img src="./logo.png" alt="Rustle" width="500"/>


[![CI 状态](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/ci.yml?branch=main&label=ci)](https://github.com/blocksecteam/rustle/actions/workflows/ci.yml)
[![构建镜像状态](https://img.shields.io/github/actions/workflow/status/blocksecteam/rustle/build-image.yml?branch=main&label=build-image)](https://github.com/blocksecteam/rustle/actions/workflows/build-image.yml)
[![许可证：AGPL v3](https://img.shields.io/github/license/blocksecteam/rustle)](LICENSE)
[![AwesomeNEAR](https://img.shields.io/badge/Project-AwesomeNEAR-054db4)](https://awesomenear.com/rustle)
[![Devpost](https://img.shields.io/badge/荣誉提名-Devpost-003e54)](https://devpost.com/software/rustle)

Rustle 是 Rust 中 NEAR 智能合约的自动静态分析器。它可以帮助定位 NEAR 智能合约中的数十种不同的漏洞。
根据 [DefiLlama](https://defillama.com/chain/Near) 的数据，在 NEAR 排名前 10 的 DApp 中，有 8 个接受了 BlockSec 的审计。凭借丰富的审计经验和对 NEAR 协议的深刻理解，我们构建了这个工具并与社区分享。

## 开始

### 先决条件

#### Linux 安装

在 Linux 中使用以下命令为 **Rustle** 安装所需的工具包。这些命令已在 Ubuntu 20.04 LTS 中测试。

```bash
# install Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# install LLVM 15
sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 15

# install Python toolchain
sudo apt install python3 python3-pip    # requires python >= 3.8
pip3 install -r utils/requirements.txt  # you need to clone this repo first

# add WASM target
rustup target add wasm32-unknown-unknown

# install other components
sudo apt install figlet
cargo install rustfilt

# [optional] useful tools for developing
LLVM_VERSION=
sudo apt install clangd-$LLVM_VERSION clang-format-$LLVM_VERSION clang-tidy-$LLVM_VERSION
```

#### macOS 设置

以下命令适用于使用 macOS 的用户，它们仅在 Apple Silicon Mac 上进行过测试，因此请谨慎使用。

```bash
# install Rust Toolchain
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# install LLVM 15
brew install llvm@15

# install Python packages
pip3 install -r utils/requirements.txt  # you need to clone this repo first
                                        # using macOS default python3

# add WASM target
rustup target add wasm32-unknown-unknown

# install other components
brew install figlet coreutils gsed
cargo install rustfilt
```

#### Docker

我们提供一个 Docker 解决方案。

```bash
# build the image
docker build --build-arg UID=`id -u` --build-arg GID=`id -g` -t rustle .

# run a container from the image
docker run --name rustle -it -v `pwd`:/rustle -w /rustle rustle bash

# exec the container
docker start rustle
docker exec -it -w /rustle rustle bash
```

### 用法

```bash
./rustle [-t|--tg_dir <tg_dir>] [-d|--detector <detector_list>] [-o|--output <output_dir>] [-h|--help] <src_dir>
```

* `src_dir`：合同源代码的路径。
* `tg_dir`：合约构建目标的路径。默认与`src_dir`相同。
* `detector`：检测器列表。它可以用来传递多个*检测器*或用`,`分隔的*组*。默认值为`all`。
  *   传递 `all` *参数* 以启用所有检测器。
  *   传递 `high`、`medium`、`low` 和 `info` *组* 以启用具有不同严重性等级的检测器组（参考[检测器](#detectors)）
  *   传递 `nep-ft`、`nep-storage` 和 `nep-nft` *组* 以启用为特定 NEP 实现的检测器（参考 [NEP 检测器组](#nep-detector-groups)）
  *   在[表格](#detectors)中传递*探测器ID*以启用这些探测器
* `output`：审计报告将生成在此路径中。默认为 `./audit-result`。

注意：如果由 cargo 构建的目标位码（`.bc` 二进制文件）不在 `$src_dir` 中，请使用 `-t|--tg_dir` 来设置目标的目录，否则它将默认设置为 `$src_dir`。

下面的命令展示了一个分析LiNEAR的例子。

```bash
# clone LiNEAR
git clone https://github.com/linear-protocol/LiNEAR.git ~/near-repo/LiNEAR

# run Rustle
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear

# [optional] run Rustle on specified detectors or severity groups and save audit reports in `~/linear-report`
./rustle -t ~/near-repo/LiNEAR ~/near-repo/LiNEAR/contracts/linear -d high,medium,complex-loop -o ~/linear-report
```

一个CSV格式的报告将会在“./audit-result”目录中生成。

## 探测器

**Rustle**可以找到的所有漏洞。

|探测器ID|描述|严重性|
|---|---|---|
|`unhandled-promise`|[查找未处理的`Promise`](docs/detectors/unhandled-promise.md)|高|
|`non-private-callback`|[缺少宏 `#[private]` 用于回调函数](docs/detectors/non-private-callback.md)|高|
|`重入性`|[查找容易受到重入攻击的函数](docs/detectors/reentrancy.md)|高|
|`unsafe-math`|[算术操作缺乏溢出检查](docs/detectors/unsafe-math.md)|高|
|`self-transfer`|[未检查`sender != receiver`](docs/detectors/self-transfer.md)|高|
|`incorrect-json-type`|[参数或返回值中使用了错误的类型](docs/detectors/incorrect-json-type.md)|高|
|`unsaved-changes`|[集合的更改未被保存](docs/detectors/unsaved-changes.md)|高|
|`nft-approval-check`|[查找未检查`approval id`的`nft_transfer`](docs/detectors/nft-approval-check.md)|高|
|`nft-owner-check`|[查找未进行所有者检查的批准或撤销功能](docs/detectors/nft-owner-check.md)|高|
|`div-before-mul`|[由于操作顺序不当导致的精度损失](docs/detectors/div-before-mul.md)|中等|
|`round`|[不指定向上或向下取整的舍入](docs/detectors/round.md)|中等|
|`lock-callback`|[回调函数中的panic可能会锁定合约](docs/detectors/lock-callback.md)|中等|
|`yocto-attach`|[在特权函数中没有 `assert_one_yocto`](docs/detectors/yocto-attach.md)|中等|
|`dup-collection-id`|[集合中使用的重复 id](docs/detectors/dup-collection-id.md)|中等|
|`unregistered-receiver`|[未注册接收者不会引起恐慌](docs/detectors/unregistered-receiver.md)|中等|
|`nep${id}-interface`|[查找所有未实现的NEP接口](docs/detectors/nep-interface.md)|中等|
|`prepaid-gas`|[`ft_transfer_call`中缺少预付气体检查](docs/detectors/prepaid-gas.md)|低|
|`non-callback-private`|[在非回调函数中使用的宏 `#[private]`](docs/detectors/non-callback-private.md)|低|
|`unused-ret`|[函数结果未使用或未检查](docs/detectors/unused-ret.md)|低|
|`upgrade-func`|[合约中无升级功能](docs/detectors/upgrade-func.md)|低|
|`重言式`|[条件分支中使用的重言式](docs/detectors/tautology.md)|低|
|`storage-gas`|[缺少存储扩展的余额检查](docs/detectors/storage-gas.md)|低|
|`unclaimed-storage-fee`|[存储注销前缺少余额检查](docs/detectors/unclaimed-storage-fee.md)|低|
|`不一致`|[使用相似但略有不同的符号](docs/detectors/inconsistency.md)|信息|
|`timestamp`|[查找所有 `timestamp` 的用途](docs/detectors/timestamp.md)|信息|
|`complex-loop`|[查找所有可能导致DoS的复杂逻辑循环](docs/detectors/complex-loop.md)|信息|
|`ext-call`|[查找所有跨合约调用](docs/detectors/ext-call.md)|信息|
|`promise-result`|[查找所有 promise 结果的用途](docs/detectors/promise-result.md)|信息|
|`transfer`|[查找所有转账动作](docs/detectors/transfer.md)|信息|
|`public-interface`|[查找所有公共接口](docs/detectors/public-interface.md)|信息|

### NEP 检测器组

除了按严重性级别分组外，**Rustle**还提供了一些按相应NEP划分的检测器组。目前，**Rustle**支持以下组。


|NEP|探测器组ID|探测器ID|
|---|---|---|
|[NEP-141][nep141]|`nep-ft`|`nep141-interface`、`self-transfer`、`unregistered-receiver`|
|[NEP-145][nep145]|`nep-storage`|`nep145-interface`，`unclaimed-storage-fee`|
|[NEP-171][nep171]，[NEP-178][nep178]|`nep-nft`|`nep171-interface`，`nft-approval-check`，`nft-owner-check`|

## 添加新的探测器

1. 将这个仓库Fork到你的账户。
2. 将新探测器放置在[/detectors](/detectors/)下。
3. 在[/Makefile](/Makefile)中添加一个检测目标，其中包含用于运行检测器的命令。
4. 将目标添加到 `audit` 目标的依赖中，并将其名称添加到 `./rustle` 脚本中的[探测器列表](/rustle#L146)和[严重性分组](/rustle#L169)。
5. 在 [utils/audit.py](/utils/audit.py) 中添加处理代码（参考 `audit.py` 中其他检测器的代码）。
6. 从你的分支向主分支提交一个拉取请求。

## 注意

**Rustle** 可以在开发过程中用于迭代扫描 NEAR 智能合约。这可以节省大量的手动劳力并减轻部分潜在问题。然而，复杂逻辑或与语义相关的漏洞仍是 **Rustle** 的局限。定位复杂的语义问题需要 [BlockSec](https://blocksec.com/) 的专家进行全面而彻底的审查。[联系我们](mailto:audit@blocksec.com) 获取审计服务。

## 许可证

该项目遵循 AGPLv3 许可证。有关完整的许可证文本，请参阅 [LICENSE](LICENSE) 文件。
