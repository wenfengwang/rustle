
## NFT転送時の承認IDチェックの欠如

### 設定

* 検出器ID: `nft-owner-check`
* 重大度: 高

### 説明

[NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md)の設計において、NFTの所有者は指定されたインターフェース（例えば、`nft_approve`、`nft_revoke`、`nft_revoke_all`）を使用して承認を与えたり取り消したりすることができます。これらのインターフェースには所有者のみが呼び出せることを確認するための所有者チェックを実装する必要があります。そうでなければ、誰でもNFTの承認を変更することができてしまいます。

### サンプルコード

[near-contract-standards](https://github.com/near/near-sdk-rs/blob/a903f8c44a7be363d960838d92afdb22d1ce8b87/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs)にあるコードは正しい実装を示しています。

```rust
// `nft_approve`、`nft_revoke`、`nft_revoke_all`に対して実装されるべきです
let owner_id = expect_token_found(self.owner_by_id.get(&token_id));
let predecessor_account_id = env::predecessor_account_id();

require!(predecessor_account_id == owner_id, "Predecessor must be token owner.");
```
