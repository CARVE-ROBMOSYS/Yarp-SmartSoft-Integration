/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SMARTSOFT_SMARTVOCABS_H
#define YARP_SMARTSOFT_SMARTVOCABS_H

#include <yarp/os/Vocab.h>

namespace yarp {
namespace smartsoft {

// Query pattern

constexpr yarp::conf::vocab32_t  vocab_query_request      = yarp::os::createVocab('q','r','e','q');
constexpr yarp::conf::vocab32_t  vocab_query_receive      = yarp::os::createVocab('q','r','e','c');
constexpr yarp::conf::vocab32_t  vocab_query_receive_wait = yarp::os::createVocab('q','r','e','w');
constexpr yarp::conf::vocab32_t  vocab_query_discard      = yarp::os::createVocab('q','d','i','s');
constexpr yarp::conf::vocab32_t  vocab_query_not_ready    = yarp::os::createVocab('q','n','r');
constexpr yarp::conf::vocab32_t  vocab_query_wrong_id     = yarp::os::createVocab('q','w','i','d');
constexpr yarp::conf::vocab32_t  vocab_query_id           = yarp::os::createVocab('q','i','d');

}
}

#endif // YARP_SMARTSOFT_SMARTVOCABS_H
