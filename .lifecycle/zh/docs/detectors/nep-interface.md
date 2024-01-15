## 检查 NEP 接口的完整性

### 配置

* 探测器 id: `nep${id}-interface`（`${id}` 是 NEP 编号）
* 严重性：中

### 描述

[NEPs](https://github.com/near/NEPs) 代表 NEAR 增强提案，它们是对 NEAR 协议规范和标准的一些更改。目前，有关于 FT、NFT、MT 和存储的 NEPs，它们被列在一个[表格](https://github.com/near/NEPs#neps)中。

要使用这个探测器，你需要在探测器的ID中指定NEP编号，例如：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non Fungible Token Standard
```

### 示例代码

检测器`nep-interface`的[示例](/examples/nep-interface/)改编自接近合约标准。