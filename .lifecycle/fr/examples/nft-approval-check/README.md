
# Exemple du détecteur `nft-approval-check`

Cet exemple est basé sur l'implémentation des [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs). Toutefois, une nouvelle fonction [`internal_transfer_unsafe`](src/lib.rs#L256) a été ajoutée. Dans cette fonction, la vérification de `approval_id` est omise, ce qui est incorrect.

L'interface `nft_transfer` va appeler ce nouveau `internal_transfer_unsafe` non sécurisé alors que `nft_transfer_call` continuera d'utiliser le `internal_transfer` sécurisé. Par conséquent, le **Rustle** signalera le `nft_transfer` comme étant non sécurisé.
