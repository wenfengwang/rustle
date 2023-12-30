
<a name="v2.0"></a>
# [v2.0](https://github.com/blocksecteam/rustle/releases/tag/v2.0) - 2023 年 4 月 7 日

## 变更内容

* 新增对 macOS 的支持，请参考 [README](/README.md#macos-setup) 了解更多信息

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.3...v2.0

[变更详情][v2.0]

<a name="v1.3"></a>
# [v1.3](https://github.com/blocksecteam/rustle/releases/tag/v1.3) - 2023 年 1 月 13 日

## 变更内容

* 新增 3 个检测器
  *   [unclaimed-storage-fee](/docs/detectors/unclaimed-storage-fee.md)：查找在取消注册存储前未进行余额检查的函数（基于 [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md)）
  *   [nft-approval-check](/docs/detectors/nft-approval-check.md)：查找未检查 `approval id` 的 `nft_transfer` 函数（基于 [NEP-171](https://github.com/near/NEPs/blob/master/neps/nep-0171.md)）
  *   [nft-owner-check](/docs/detectors/nft-owner-check.md)：查找未进行所有者检查的授权或撤销函数（基于 [NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md)）
* 新增检测器组 `nep-ft`、`nep-storage` 和 `nep-nft`

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.2...v1.3

[变更详情][v1.3]

<a name="v1.2"></a>
# [v1.2](https://github.com/blocksecteam/rustle/releases/tag/v1.2) - 2022 年 12 月 16 日

## 变更内容

* 新增 6 个检测器
  *   [public-interface](/docs/detectors/public-interface.md)：查找所有公开接口
  *   [dup-collection-id](/docs/detectors/dup-collection-id.md)：查找集合中使用的重复 id
  *   [storage-gas](/docs/detectors/storage-gas.md)：查找存储扩展时遗漏的余额检查
  *   [unregistered-receiver](/docs/detectors/unregistered-receiver.md)：查找对未注册接收者的转账函数没有进行异常处理
  *   [unsaved-changes](/docs/detectors/unsaved-changes.md)：查找未保存的集合更改
  *   [nep${id}-interface](/docs/detectors/nep-interface.md)：对不同 NEP 规范进行接口完整性检查
* 新增对 rustc v1.65.0 的支持
* 集成 clang-tidy 以优化代码

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.1...v1.2

[变更详情][v1.2]

<a name="v1.1"></a>
# [v1.1](https://github.com/blocksecteam/rustle/releases/tag/v1.1) - 2022 年 11 月 10 日

## 变更内容

* 文档：为每个检测器添加了[示例](/examples)
* 功能：将 LLVM 版本升级到 15（但我们仍在努力支持 Rust v1.65.0，请参考此 [PR](https://github.com/rust-lang/rust/pull/99464/) 获取更多信息）
* 功能：新增单元测试脚本
* 功能：向 [rustle](/rustle) 脚本添加 `--output` 参数
* 功能：在审计报告中按严重性等级划分漏洞
* 修复若干错误

**完整变更日志**：https://github.com/blocksecteam/rustle/compare/v1.0...v1.1

[变更详情][v1.1]

<a name="v1.0"></a>
# [v1.0](https://github.com/blocksecteam/rustle/releases/tag/v1.0) - 2022 年 11 月 1 日

我们很高兴发布 [Rustle](https://github.com/blocksecteam/rustle)：由 [BlockSec](https://blocksec.com/) 为 NEAR 社区提供的首个自动审计工具。

Rustle 具有以下几个显著特点：

* Rustle 目前能够检测 NEAR 合约中的 20 多种问题。完整的检测器列表请参见检测器部分。
* Rustle 使用简便。我们提供了详尽的安装指令和教程。此外，我们还为用户准备了一个 Docker 镜像以便快速开始。
* Rustle 分析速度快，大多数 NEAR 合约能在 3 分钟内完成分析。
* Rustle 提供 CSV 和 JSON 格式的报告，用户体验良好。我们还提供了一个脚本帮助您将结果导入到 [Notion](https://www.notion.so/)。

[变更详情][v1.0]


<!-- 由 https://github.com/rhysd/changelog-from-release v3.7.0 生成 -->

