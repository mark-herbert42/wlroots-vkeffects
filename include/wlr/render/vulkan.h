/*
 * This an unstable interface of wlroots. No guarantees are made regarding the
 * future consistency of this API.
 */
#ifndef WLR_USE_UNSTABLE
#error "Add -DWLR_USE_UNSTABLE to enable unstable wlroots features"
#endif

#ifndef WLR_RENDER_VULKAN_H
#define WLR_RENDER_VULKAN_H

#include <vulkan/vulkan_core.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/render/color.h>
#include <pixman.h>

struct wlr_vk_image_attribs {
	VkImage image;
	VkImageLayout layout;
	VkFormat format;
};

struct wlr_renderer *wlr_vk_renderer_create_with_drm_fd(int drm_fd);

VkInstance wlr_vk_renderer_get_instance(struct wlr_renderer *renderer);
VkPhysicalDevice wlr_vk_renderer_get_physical_device(struct wlr_renderer *renderer);
VkDevice wlr_vk_renderer_get_device(struct wlr_renderer *renderer);
uint32_t wlr_vk_renderer_get_queue_family(struct wlr_renderer *renderer);

VkCommandBuffer wlr_vk_render_pass_get_command_buffer(struct wlr_render_pass *pass);
VkRenderPass wlr_vk_render_pass_get_render_pass(struct wlr_render_pass *pass);
VkPipeline wlr_vk_render_pass_get_bound_pipeline(struct wlr_render_pass *pass);
void wlr_vk_render_pass_set_bound_pipeline(struct wlr_render_pass *pass,
		VkPipeline pipeline);
void wlr_vk_render_pass_reset_pipeline(struct wlr_render_pass *pass);
VkDescriptorSetLayout wlr_vk_render_pass_get_texture_ds_layout(struct wlr_render_pass *pass,
	struct wlr_texture *texture, enum wlr_scale_filter_mode filter_mode, enum wlr_color_transfer_function tf);
VkDescriptorSet wlr_vk_render_pass_get_texture_ds(struct wlr_render_pass *pass,
	struct wlr_texture *texture, enum wlr_scale_filter_mode filter_mode, enum wlr_color_transfer_function tf);
void wlr_vk_render_pass_mark_updated(struct wlr_render_pass *pass, pixman_region32_t *updated);

typedef void (*wlr_vk_render_pass_resource_callback_t)(void *data);
void wlr_vk_render_pass_set_resources_callback(struct wlr_render_pass *pass,
		wlr_vk_render_pass_resource_callback_t callback, void *data);

bool wlr_renderer_is_vk(struct wlr_renderer *wlr_renderer);
bool wlr_texture_is_vk(struct wlr_texture *texture);

void wlr_vk_texture_get_image_attribs(struct wlr_texture *texture,
	struct wlr_vk_image_attribs *attribs);

bool wlr_vk_texture_has_alpha(struct wlr_texture *texture);

#endif

