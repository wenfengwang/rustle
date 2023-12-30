
# 検出器 `nft-owner-check` の例

この例は、[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs)の実装に基づいています。しかし、関数[`nft_revoke_all`](src/lib.rs#L171)から所有者のチェックが削除されています。その結果、誰でもこの関数を呼び出してNFTへの全ての承認を取り消すことが可能になるため、インターフェースは安全ではなくなります。
