#include "logica.h"
#include <stdio.h>
#include <stdbool.h>

static const char *vf(bool b) { return b ? "V" : "F"; }

bool logica_avaliar(const Fase *fase) {
    bool P = fase->variaveis[0];
    bool Q = fase->variaveis[1];
    bool R = fase->variaveis[2];

    switch (fase->proposicao) {
        case PROP_E:            return P && Q;
        case PROP_OU:           return P || Q;
        case PROP_NAO_P_E_Q:    return (!P) && Q;
        case PROP_IMPLICA:      return (!(P && Q)) || R;   /* (P /\ Q) -> R */
        case PROP_BICONDICIONAL: return P == Q;
        case PROP_NAND_R:        return !(P && Q) && R;
        case PROP_BICOND_IMPL:   return (P == Q) && (!R || fase->variaveis[3]);
    }
    return false;
}

void logica_descricao(const Fase *fase, char *out_linha1, char *out_linha2, char *out_linha3) {
    bool P = fase->variaveis[0];
    bool Q = fase->variaveis[1];
    bool R = fase->variaveis[2];
    bool resultado = logica_avaliar(fase);
    const char *res = vf(resultado);

    switch (fase->proposicao) {
        case PROP_E:
            snprintf(out_linha1, 64, "P = %s,  Q = %s", vf(P), vf(Q));
            snprintf(out_linha2, 64, "P /\\ Q = %s", res);
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_OU:
            snprintf(out_linha1, 64, "P = %s,  Q = %s", vf(P), vf(Q));
            snprintf(out_linha2, 64, "P \\/ Q = %s", res);
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_NAO_P_E_Q:
            snprintf(out_linha1, 64, "P = %s,  Q = %s", vf(P), vf(Q));
            snprintf(out_linha2, 64, "~P = %s,  ~P /\\ Q = %s", vf(!P), res);
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_IMPLICA:
            snprintf(out_linha1, 64, "P=%s  Q=%s  R=%s", vf(P), vf(Q), vf(R));
            snprintf(out_linha2, 64, "(P /\\ Q)=%s,  (P/\\Q)->R = %s", vf(P && Q), res);
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_BICONDICIONAL:
            snprintf(out_linha1, 64, "P = %s,  Q = %s", vf(P), vf(Q));
            snprintf(out_linha2, 64, "P <-> Q = %s", res);
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_NAND_R:
            snprintf(out_linha1, 64, "P = %s,  Q = %s,  R = %s", vf(P), vf(Q), vf(R));
            snprintf(out_linha2, 64, "~(P/\\Q) = %s,  /\\ R = %s", vf(!(P&&Q)), vf(R));
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        case PROP_BICOND_IMPL: {
            bool S = fase->variaveis[3];
            snprintf(out_linha1, 64, "P=%s  Q=%s  R=%s  S=%s", vf(P), vf(Q), vf(R), vf(S));
            snprintf(out_linha2, 64, "P<->Q=%s,  R->S=%s", vf(P == Q), vf(!R || S));
            snprintf(out_linha3, 64, "Porta: %s", resultado ? "ABERTA" : "FECHADA");
            break;
        }
    }
}
