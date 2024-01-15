
## NEP インターフェースの整合性をチェックする

### 設定

* 検出器 ID: `nep${id}-interface` (`${id}` は NEP ID)
* 重大度: 中

### 説明

[NEPs](https://github.com/near/NEPs) は、NEAR Enhancement Proposals の略で、NEAR プロトコルの仕様や標準に対する変更案を指します。現在、FT、NFT、MT、ストレージに関する NEPs が [一覧表](https://github.com/near/NEPs#neps) にリストされています。

この検出器を使用するには、検出器 ID に NEP の ID を指定する必要があります。例えば：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non-Fungible Token Standard
```

### サンプルコード

`nep-interface` 検出器の[例](/examples/nep-interface/)は near-contract-standards から採用されています。
