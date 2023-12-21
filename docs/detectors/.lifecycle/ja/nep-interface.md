
## NEP インターフェースの整合性をチェックする

### 設定

* detector id: `nep${id}-interface` (`${id}` は NEP の ID)
* 重大度: 中

### 説明

[NEPs](https://github.com/near/NEPs)はNear Enhancement Proposalsの略で、NEARプロトコルの仕様や標準に対する変更案を指します。現在、FT、NFT、MT、ストレージに関するNEPsが[一覧表](https://github.com/near/NEPs#neps)にリストされています。

このdetectorを使用するには、detector idにNEPのidを指定する必要があります。例えば以下のようになります:

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non-Fungible Token Standard
```

### サンプルコード

`nep-interface` detectorの[例](/examples/nep-interface/)は、near-contract-standardsから採用されています。
