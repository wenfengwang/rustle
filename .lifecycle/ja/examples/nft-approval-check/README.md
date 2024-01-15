
# 検出器 `nft-approval-check` の例

この例は、[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs)の実装を基にしています。しかし、新たな関数[`internal_transfer_unsafe`](src/lib.rs#L256)が追加されています。この関数では、`approval_id`のチェックが削除されており、これは不正確です。

インターフェイス`nft_transfer`はこの新しい安全でない`internal_transfer_unsafe`を呼び出しますが、`nft_transfer_call`は依然として安全な`internal_transfer`を使用します。そのため、**Rustle**は`nft_transfer`を安全でないものとしてマークするでしょう。
