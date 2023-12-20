
## 检查 NEP 接口的完整性

### 配置

* 检测器 ID：`nep${id}-interface`（`${id}` 是 NEP ID）
* 严重程度：中等

### 描述

[NEPs](https://github.com/near/NEPs) 代表 NEAR 增强提案，这些提案是对 NEAR 协议规范和标准的一些更改。目前，FT、NFT、MT 和存储的 NEP 已列在一个[表格](https://github.com/near/NEPs#neps)中。

要使用此检测器，您需要在检测器 ID 中指定 NEP id，例如：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token 标准
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # 存储管理
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non-Fungible Token 标准
```

### 示例代码

检测器 `nep-interface` 的[示例](/examples/nep-interface/)是根据 near-contract-standards 改编的。