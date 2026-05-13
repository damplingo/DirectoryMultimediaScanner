#pragma once

#include <userver/components/component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/component.hpp>
#include "TDirectoryScaner.h"
#include <string_view>
#include <memory>

class THttpHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler";

    THttpHandler(const userver::components::ComponentConfig& config,
                      const userver::components::ComponentContext& context);
    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request, userver::server::request::RequestContext&) const override;
    static void SetScanner(std::shared_ptr<TDirectoryScaner> scanner);
private:
    static std::shared_ptr<TDirectoryScaner> scanner_;
};

namespace NHttpHandler {
    void AppendHandler(userver::components::ComponentList& componentList);
}