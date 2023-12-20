
## 检查NEP接口的完整性

### 配置

* 检测器ID：`nep${id}-interface`（`${id}`是NEP ID）
* 严重程度：中等

### 描述

[NEPs](https://github.com/near/NEPs)代表NEAR增强提案，这些提案是对NEAR协议规范和标准的一些更改。目前，包括FT、NFT、MT和存储在内的NEP已列在一个[表格](https://github.com/near/NEPs#neps)中。

要使用这个检测器，你需要在检测器ID中指定NEP的ID，例如：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non Fungible Token Standard
```

### 示例代码

`nep-interface`检测器的[示例](/examples/nep-interface/)是根据near-contract-standards改编的。