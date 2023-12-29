
<a name="v2.0"></a>
# [v2.0](https://github.com/blocksecteam/rustle/releases/tag/v2.0) - 2023年4月7日

## 变更内容

* 添加对macOS的支持，更多信息请参考[README](/README.md#macos-setup)

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.3...v2.0

[变更详情][v2.0]

<a name="v1.3"></a>
# [v1.3](https://github.com/blocksecteam/rustle/releases/tag/v1.3) - 2023年1月13日

## 变更内容

* 新增3个探测器
  *   [unclaimed-storage-fee](/docs/detectors/unclaimed-storage-fee.md)：寻找在存储注销前未进行余额检查的函数（基于[NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md)）
  *   [nft-approval-check](/docs/detectors/nft-approval-check.md)：寻找未检查`approval id`的`nft_transfer`（基于[NEP-171](https://github.com/near/NEPs/blob/master/neps/nep-0171.md)）
  *   [nft-owner-check](/docs/detectors/nft-owner-check.md)：寻找未进行所有者检查的授权或撤销函数（基于[NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md)）
* 新增探测器组`nep-ft`、`nep-storage`和`nep-nft`

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.2...v1.3

[变更详情][v1.3]

<a name="v1.2"></a>
# [v1.2](https://github.com/blocksecteam/rustle/releases/tag/v1.2) - 2022年12月16日

## 变更内容

* 新增6个探测器
  *   [public-interface](/docs/detectors/public-interface.md)：寻找所有公开接口
  *   [dup-collection-id](/docs/detectors/dup-collection-id.md)：寻找集合中使用了重复id的情况
  *   [storage-gas](/docs/detectors/storage-gas.md)：寻找存储扩展时缺失的余额检查
  *   [unregistered-receiver](/docs/detectors/unregistered-receiver.md)：寻找对未注册接收者的转账函数没有进行panic处理的情况
  *   [unsaved-changes](/docs/detectors/unsaved-changes.md)：寻找集合更改未被保存的情况
  *   [nep${id}-interface](/docs/detectors/nep-interface.md)：对不同NEP规范进行接口完整性检查
* 支持rustc v1.65.0
* 集成clang-tidy进行代码优化

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.1...v1.2

[变更详情][v1.2]

<a name="v1.1"></a>
# [v1.1](https://github.com/blocksecteam/rustle/releases/tag/v1.1) - 2022年11月10日

## 变更内容

* 文档：为每个探测器添加[示例](/examples)
* 功能：将LLVM版本升级到15（但我们仍在努力支持Rust v1.65.0，请参考此[PR](https://github.com/rust-lang/rust/pull/99464/)获取更多信息）
* 功能：添加单元测试脚本
* 功能：为[rustle](/rustle)脚本添加`--output`标志
* 功能：在审计报告中按不同严重性等级划分漏洞
* 修复若干bug

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.0...v1.1

[变更详情][v1.1]

<a name="v1.0"></a>
# [v1.0](https://github.com/blocksecteam/rustle/releases/tag/v1.0) - 2022年11月1日

我们非常高兴地发布[Rustle](https://github.com/blocksecteam/rustle)：由[BlockSec](https://blocksec.com/)为NEAR社区提供的首个自动审计工具。

Rustle具有以下几个优秀特性：

* Rustle目前能够检测NEAR合约中20多种类型的问题。完整的探测器列表请参见探测器部分。
* Rustle使用简便。我们提供了详尽的安装命令和教程。此外，我们还为用户准备了一个docker以便快速开始使用。
* Rustle分析速度快，大多数NEAR合约能在3分钟内完成分析。
* Rustle提供CSV和JSON格式的报告，用户体验友好。我们还提供了一个脚本帮助您将结果导入到[Notion](https://www.notion.so/)。

[变更详情][v1.0]


<!-- 由https://github.com/rhysd/changelog-from-release v3.7.0生成 -->

