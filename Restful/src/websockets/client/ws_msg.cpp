#include "stdafx.h"
#include "../../http/common/internal_http_helpers.h"

#if !defined(CPPREST_EXCLUDE_WEBSOCKETS)

using namespace concurrency;
using namespace concurrency::streams::details;

namespace web
{
namespace websockets
{
namespace client
{

static ::utility::string_t g_subProtocolHeader = _XPLATSTR("Sec-WebSocket-Protocol");
void websocket_client_config::add_subprotocol(const ::utility::string_t &name)
{
    m_headers.add(g_subProtocolHeader, name);
}

std::vector<::utility::string_t> websocket_client_config::subprotocols() const
{
    std::vector<::utility::string_t> values;
    auto subprotocolHeader = m_headers.find(g_subProtocolHeader);
    if (subprotocolHeader != m_headers.end())
    {
        utility::stringstream_t header(subprotocolHeader->second);
        utility::string_t token;
        while (std::getline(header, token, U(',')))
        {
            http::details::trim_whitespace(token);
            if (!token.empty())
            {
                values.push_back(token);
            }
        }
    }
    return values;
}

pplx::task<std::string> websocket_incoming_message::extract_string() const
{
    if (m_msg_type == websocket_message_type::binary_message)
    {
        return pplx::task_from_exception<std::string>(websocket_exception("Invalid message type"));
    }
    return pplx::task_from_result(std::move(m_body.collection()));
}

}}}

#endif
