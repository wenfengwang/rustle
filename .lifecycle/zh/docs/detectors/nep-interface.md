## 检查 NEP 接口的完整性

### 配置

* 检测器 ID： `nep${id}-interface` （`${id}` 为 NEP ID）
* 严重性：中等

### 描述

[NEP](https://github.com/near/NEPs) 代表 NEAR Enhancement Proposals，这些是对 NEAR 协议规范和标准的一些更改。目前，有关 FT、NFT、MT 和存储的 NEP 列在[表格](https://github.com/near/NEPs#neps)中。

要使用此检测器，您需要在检测器 ID 中指定 NEP ID，例如：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # 可替代代币标准
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # 存储管理
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # 非同质化代币标准
```

### 示例代码

[示例](/examples/nep-interface/)中的 `nep-interface` 检测器改编自 near-contract-standards。